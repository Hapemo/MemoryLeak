/*!*****************************************************************************
\file RenderManager.cpp
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function definitions for the class RenderManager, which
operates on Entities with Sprite and Transform Components.
*******************************************************************************/
#include "Graphics/RenderManager.h"
#include "pch.h"

//define number of triangles for circle
constexpr int CIRCLE_SLICES = 18;
//modifier for vector.reserve() 
constexpr float MODIFIER = 0.05f;
constexpr size_t NO_OF_OBJECTS = 10000;
constexpr size_t VERTICES_PER_OBJECT = 4;
constexpr size_t INDICES_PER_OBJECT = 6;
//maximum used texture units in 1 draw call
constexpr size_t TEXTURES_PER_DRAW = 16;

/*!*****************************************************************************
\brief
Default Constructor for RenderManager class.
*******************************************************************************/
RenderManager::RenderManager()
	: mAllocator(NO_OF_OBJECTS, VERTICES_PER_OBJECT, INDICES_PER_OBJECT),
	mWorldFBO(), mGameFBO(), mDefaultProgram("shaders/default.vert", "shaders/default.frag"),
	mTextureProgram("shaders/texture.vert", "shaders/texture.frag"),
	mWindowHeight(nullptr), mWindowWidth(nullptr)
{
	//set debug mode to true
	mDebug = true;
	//render world (editor)
	mRenderGameToScreen = true;
	mCurrRenderPass = RENDER_STATE::GAME;
	mVectorLengthModifier = 50.f;

	//initialize opengl values
	glClearColor(0.537f, 0.812f, 0.941f, 1.f);
	glPointSize(8.f);
	glLineWidth(2.f);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitializeShaders();
	
	//reserve space in vectors
	mVertices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * VERTICES_PER_OBJECT));
	mIndices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * INDICES_PER_OBJECT));
	mTextureVertices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * VERTICES_PER_OBJECT));
	mTextureIndices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * INDICES_PER_OBJECT));
	mDebugPoints.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER));
	mDebugVertices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * VERTICES_PER_OBJECT));
	mDebugIndices.reserve(static_cast<uint64_t>(NO_OF_OBJECTS * MODIFIER * INDICES_PER_OBJECT));
}

/*!*****************************************************************************
\brief
Initializes the RenderManager class.

\param int* _windowWidth
Pixel width of the window.

\param int* _windowHeight
Pixel height of the window.
*******************************************************************************/
void RenderManager::Init(int* _windowWidth, int* _windowHeight) {
	mWindowWidth = _windowWidth;
	mWindowHeight = _windowHeight;
	mFontManager.Init();
	//initialize fbo with window width and height
	mWorldFBO.Init(*mWindowWidth, *mWindowHeight);
	mGameFBO.Init(*mWindowWidth, *mWindowHeight);
	mWorldCam.Init(*mWindowWidth, *mWindowHeight);
	mGameCam.Init(*mWindowWidth, *mWindowHeight);
}

/*!*****************************************************************************
\brief
Render Entities with Sprite and Transform Component.
*******************************************************************************/
void RenderManager::Render()
{
	if (!mRenderGameToScreen)
		mCurrRenderPass == RENDER_STATE::GAME ? 
		mGameFBO.Bind() : mWorldFBO.Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::map<GLuint, TextureInfo> textureInfo;
	int samplerUniform[TEXTURES_PER_DRAW];
	for (int i = 0; i < TEXTURES_PER_DRAW; ++i)
		samplerUniform[i] = i;

	/*************************************CREATING VERTICES START************************************/
	//creating squares and circles based on Sprite component
	for (const Entity& e : mEntities)
	{
		if (!e.GetComponent<General>().isActive) continue;

		switch (e.GetComponent<Sprite>().sprite)
		{
		case SPRITE::TEXTURE:
		{
			GLuint texid = e.GetComponent<Sprite>().texture;
			if (texid != 0)
			{
				if (textureInfo.find(texid) == textureInfo.end())
					textureInfo[texid] = { (int)texid - 1, std::vector<Vertex>(), std::vector<GLushort>() };

				CreateSquare(e, textureInfo[texid].mVertices, textureInfo[texid].mIndices);
			}
		}
		break;
		case SPRITE::SQUARE:
			CreateSquare(e, mVertices, mIndices);
			break;
		case SPRITE::CIRCLE:
			CreateCircle(e);
			break;
		default:
			continue;
		}
	}
	/*************************************CREATING VERTICES END**************************************/

	/*************************************TEXTURE BATCHING START*************************************/
	//use texture program and bind VAO
	mTextureProgram.Bind();
	mAllocator.BindVAO();

	//insert uniforms
	mTextureProgram.InsertUniform1iv("uTex2D", TEXTURES_PER_DRAW, samplerUniform);

	int textureCount = 0;

	std::vector<int> usedTexUnits;
	usedTexUnits.reserve(TEXTURES_PER_DRAW);

	//iterate over texture map
	for (std::map<GLuint, TextureInfo>::iterator it = textureInfo.begin(); it != textureInfo.end(); ++it)
	{
		//if texture unit is not used, concat vertices
		if (std::find(usedTexUnits.begin(), usedTexUnits.end(), 
			it->second.mTextureUnit % TEXTURES_PER_DRAW) == usedTexUnits.end())
		{
			BindTextureUnit(it->first, it->second, usedTexUnits);
			++textureCount;

			//if all texture units are used, draw
			if (textureCount == TEXTURES_PER_DRAW)
				BatchRenderTextures(textureCount, usedTexUnits);
		}
		//if texture unit is used, render
		else
		{
			BatchRenderTextures(textureCount, usedTexUnits);
			BindTextureUnit(it->first, it->second, usedTexUnits);
			++textureCount;
		}
	}
	//render remaining textures if any
	BatchRenderTextures(textureCount, usedTexUnits);

	//unuse VAO and texture program
	mAllocator.UnbindVAO();
	mTextureProgram.Unbind();
	/**************************************TEXTURE BATCHING END**************************************/

	/***********************************SHAPES/DEBUG BATCHING START**********************************/
	//use normal program for drawing shapes
	mDefaultProgram.Bind();
	mAllocator.BindVAO();

	//render all shapes
	BatchRenderElements(GL_TRIANGLES, mVertices, mIndices);

	if (mCurrRenderPass == RENDER_STATE::WORLD || (mDebug && mRenderGameToScreen))
		RenderDebug();

	//unuse VAO and normal program
	mAllocator.UnbindVAO();
	mDefaultProgram.Unbind();
	/***********************************SHAPES/DEBUG BATCHING END************************************/

	if (!mRenderGameToScreen)
	{
		mCurrRenderPass == RENDER_STATE::GAME ? 
		mGameFBO.Unbind() : mWorldFBO.Unbind();
		mCurrRenderPass = mCurrRenderPass == RENDER_STATE::GAME ? 
		RENDER_STATE::WORLD : RENDER_STATE::GAME;
	}

	//clear vertices for next iteration
	mVertices.clear();
	mIndices.clear();
	mTextureVertices.clear();
	mTextureIndices.clear();
	mDebugPoints.clear();
	mDebugVertices.clear();
	mDebugIndices.clear();

	if (mCurrRenderPass == RENDER_STATE::WORLD)
		Render();
}

/*!*****************************************************************************
\brief
Clears the background. Mainly used for switching states.
*******************************************************************************/
void RenderManager::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*!*****************************************************************************
\brief
Function that returns the transform of an Entity for use with ImGuizmo

\param const Entity& _e
Entity to get the Transformation matrix of.

\return std::vector<float>
Transformation matrix of the Entity.
*******************************************************************************/
std::vector<float> RenderManager::GetImGuizmoMat4(const Entity& _e)
{
	Math::Mat3 temp = GetTransform(_e);
	std::vector<float> ret; 
	ret.reserve(16);

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
		{
			ret.push_back(temp[(short)i][j]);
			if (j == 1)
			{
				ret.push_back(0);
				ret.push_back(0);
			}
		}
	ret.push_back(0);
	ret.push_back(0);
	ret.push_back(1);
	ret.push_back(0);
	ret.push_back(temp[2][0]);
	ret.push_back(temp[2][1]);
	ret.push_back(0);
	ret.push_back(1);
	return ret;
}

/*!*****************************************************************************
\brief
Renders debug drawings.
*******************************************************************************/
void RenderManager::RenderDebug()
{
	if (mCurrRenderPass == RENDER_STATE::WORLD)
	{
		Transform t;
		t.rotation = 0;
		t.scale = mGameCam.GetZoom() * mGameCam.GetWindowDim();
		t.translation = mGameCam.GetPos();
		CreateDebugSquare(t, { 0, 255, 0, 255 });
	}
	for (const Entity& e : mEntities)
	{
		if (!e.GetComponent<General>().isActive) continue;

		//check if entity has any of these physics components
		if (e.HasComponent<Point2DCollider>() && e.GetComponent<Point2DCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale = { 0, 0 };
			t.rotation = 0;
			t.translation += Math::Vec2(e.GetComponent<Point2DCollider>().centerOffset.x, 
				e.GetComponent<Point2DCollider>().centerOffset.y);
			CreateDebugSquare(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<Edge2DCollider>() && e.GetComponent<Edge2DCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale *= e.GetComponent<Edge2DCollider>().scaleOffset;
			t.rotation += e.GetComponent<Edge2DCollider>().rotationOffset;
			t.translation += Math::Vec2(e.GetComponent<Edge2DCollider>().p0Offset.x,
				e.GetComponent<Edge2DCollider>().p0Offset.y);
			CreateDebugArrow(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<RectCollider>() && e.GetComponent<RectCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale.x *= e.GetComponent<RectCollider>().scaleOffset.x;
			t.scale.y *= e.GetComponent<RectCollider>().scaleOffset.y;
			t.rotation = 0;
			t.translation += Math::Vec2(e.GetComponent<RectCollider>().centerOffset.x,
				e.GetComponent<RectCollider>().centerOffset.y);
			CreateDebugSquare(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<CircleCollider>() && e.GetComponent<CircleCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale = Math::Vec2(std::max(t.scale.x, t.scale.y) * e.GetComponent<CircleCollider>().scaleOffset);
			t.rotation = 0;
			t.translation += Math::Vec2(e.GetComponent<CircleCollider>().centerOffset.x,
				e.GetComponent<CircleCollider>().centerOffset.y);
			CreateDebugCircle(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<Physics2D>() && e.GetComponent<Physics2D>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale = Math::Vec2(e.GetComponent<Physics2D>().speed) * mVectorLengthModifier;
			t.rotation = e.GetComponent<Physics2D>().moveDirection;
			CreateDebugArrow(t, e.GetComponent<Sprite>().color);
		}

		//check if sprite component itself is a debug drawing
		switch (e.GetComponent<Sprite>().sprite)
		{
		case SPRITE::DEBUG_POINT:
			CreateDebugPoint(e);
			break;
		case SPRITE::DEBUG_LINE:
			CreateDebugLine(e);
			break;
		case SPRITE::DEBUG_SQUARE:
			CreateDebugSquare(e);
			break;
		case SPRITE::DEBUG_CIRCLE:
			CreateDebugCircle(e);
			break;
		case SPRITE::DEBUG_ARROW:
			CreateDebugArrow(e);
			break;
		default:
			continue;
		}
	}

	/***************************************DEBUG BATCHING START*************************************/
	BatchRenderArrays(GL_POINTS, mDebugPoints);
	BatchRenderElements(GL_LINES, mDebugVertices, mDebugIndices);
	/***************************************DEBUG BATCHING END***************************************/

}

/*!*****************************************************************************
\brief
Binds a Texture Unit to an image.

\param const GLuint& _texID
Texture ID of the texture to be rendered.

\param const TextureInfo& _texInfo
Struct containing texture unit ID, vertices and indices.

\param std::vector<int>& _texUnits
Current texture units that are in use.
*******************************************************************************/
void RenderManager::BindTextureUnit(const GLuint& _texID, TextureInfo& _texInfo, std::vector<int>& _texUnits)
{
	glBindTextureUnit(_texInfo.mTextureUnit % TEXTURES_PER_DRAW, _texID);
	_texUnits.push_back(_texInfo.mTextureUnit % TEXTURES_PER_DRAW);
	mTextureVertices.insert(mTextureVertices.end(), _texInfo.mVertices.begin(), _texInfo.mVertices.end());
	ConcatIndices(mTextureIndices, _texInfo.mIndices);
}

/*!*****************************************************************************
\brief
Batch Rendering of vertices.

\param GLenum _mode
Mode of rendering (GL_LINES, GL_TRIANGLES, etc..)

\param const std::vector<Vertex>& _vertices
Vertices array to be rendered.
*******************************************************************************/
void RenderManager::BatchRenderArrays(GLenum _mode, const std::vector<Vertex>& _vertices)
{
	if (_vertices.empty()) return;
	glNamedBufferSubData(mAllocator.mvboid, 0, sizeof(Vertex) * _vertices.size(), _vertices.data());
	glDrawArrays(_mode, 0, static_cast<GLsizei>(_vertices.size()));
}

/*!*****************************************************************************
\brief
Batch Rendering of vertices with Element Buffer Object.

\param GLenum _mode
Mode of rendering (GL_LINES, GL_TRIANGLES, etc..)

\param const std::vector<Vertex>& _vertices
Vertices array to be rendered.

\param const std::vector<GLushort>& _indices
Indices of the vertex array.
*******************************************************************************/
void RenderManager::BatchRenderElements(GLenum _mode, const std::vector<Vertex>& _vertices, const std::vector<GLushort>& _indices)
{
	if (_vertices.empty()) return;
	glNamedBufferSubData(mAllocator.mvboid, 0, sizeof(Vertex) * _vertices.size(), _vertices.data());
	glNamedBufferSubData(mAllocator.meboid, 0, _indices.size() * sizeof(GLushort), _indices.data());
	glDrawElements(_mode, static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_SHORT, nullptr);
}

/*!*****************************************************************************
\brief
Batch Rendering of vertices with Element Buffer Object.

\param const std::vector<Vertex>& _vertices
Vertices array to be rendered.

\param const std::vector<GLushort>& _indices
Indices of the vertex array.

\param const std::vector<int>& _texUnits
Current texture units that are in use.
*******************************************************************************/
void RenderManager::BatchRenderTextures(int& _texCount, std::vector<int>& _texUnits)
{
	_texCount = 0;
	BatchRenderElements(GL_TRIANGLES, mTextureVertices, mTextureIndices);
	mTextureVertices.clear();
	mTextureIndices.clear();
	_texUnits.clear();
}

/*!*****************************************************************************
\brief
Creates a square or texture based on Transform and Sprite Component.

\param const Entity& _e
The entity containing Transform and Sprite component.

\param std::vector<Vertex>& _vertices
Vertices array for new vertices to be pushed to.

\param std::vector<GLushort>& _indices
Indices array for new indices to be pushed to.
*******************************************************************************/
void RenderManager::CreateSquare(const Entity& _e, std::vector<Vertex>& _vertices, std::vector<GLushort>& _indices)
{
	Math::Mat3 mtx = GetTransform(_e);
	glm::vec4 clr = GetColor(_e);
	float layer = (_e.GetComponent<Sprite>().layer * 2 - 255) / 255.f;
	float texID = static_cast<float>(_e.GetComponent<Sprite>().texture);

	float texMin{};
	float texMax{ 1.f };

	//calculate the new texture coordinates if component contains sheet animation.
	if (_e.HasComponent<SheetAnimation>())
	{
		float slice = texMax / (float)_e.GetComponent<SheetAnimation>().frameCount;
		float index = (float)_e.GetComponent<SheetAnimation>().currFrameIndex;

		texMin = index * slice;
		texMax = texMin + slice;
	}

	Vertex v0, v1, v2, v3;
	v0.position = (mtx * Math::Vec3(-1.f, 1.f, 1.f)).ToGLM();
	v0.position.z = layer;
	v0.color = clr;
	v0.texCoords = glm::vec2(texMin, 1.f);
	v0.texID = texID;

	v1.position = (mtx * Math::Vec3(-1.f, -1.f, 1.f)).ToGLM();
	v1.position.z = layer;
	v1.color = clr;
	v1.texCoords = glm::vec2(texMin, 0.f);
	v1.texID = texID;

	v2.position = (mtx * Math::Vec3(1.f, 1.f, 1.f)).ToGLM();
	v2.position.z = layer;
	v2.color = clr;
	v2.texCoords = glm::vec2(texMax, 1.f);
	v2.texID = texID;

	v3.position = (mtx * Math::Vec3(1.f, -1.f, 1.f)).ToGLM();
	v3.position.z = layer;
	v3.color = clr;
	v3.texCoords = glm::vec2(texMax, 0.f);
	v3.texID = texID;

	_vertices.push_back(v0);
	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);

	GLushort first = _indices.empty() ? 0 : _indices.back() + 1;
	_indices.push_back(first);
	_indices.push_back(first + 1);
	_indices.push_back(first + 2);
	_indices.push_back(first + 1);
	_indices.push_back(first + 2);
	_indices.push_back(first + 3);
}

/*!*****************************************************************************
\brief
Creates a circle based on Transform and Sprite Component.

\param const Entity& _e
The entity containing Transform and Sprite component.
*******************************************************************************/
void RenderManager::CreateCircle(const Entity& _e)
{
	Math::Mat3 mtx = GetTransform(_e);
	glm::vec4 clr = GetColor(_e);
	float layer = (_e.GetComponent<Sprite>().layer * 2 - 255.f) / 255.f;

	float theta = 2.f / CIRCLE_SLICES * 3.14159265f;
	Vertex v0;
	v0.position = (mtx * Math::Vec3(0.f, 0.f, 1.f)).ToGLM();
	v0.position.z = layer;
	v0.color = clr;
	v0.texID = 0.f;
	mVertices.push_back(v0);

	for (int i = 1; i < CIRCLE_SLICES + 2; ++i)
	{
		Vertex v;
		v.position = (mtx * Math::Vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f)).ToGLM();
		v.position.z = layer;
		v.color = clr;
		v.texID = 0.f;
		mVertices.push_back(v);
	}

	GLushort pivot = mIndices.empty() ? 0 : mIndices.back() + 1;

	for (GLushort i = 0; i < CIRCLE_SLICES; ++i)
	{
		mIndices.push_back(pivot);
		mIndices.push_back(pivot + 1 + i);
		mIndices.push_back(pivot + 2 + i);
	}
}

/*!*****************************************************************************
\brief
Creates a debug point based on Transform and Sprite Component, or Physics point
collider.

\param const Entity& _e
The entity containing Transform and Sprite component.
*******************************************************************************/
void RenderManager::CreateDebugPoint(const Entity& _e)
{
	CreateDebugPoint(_e.GetComponent<Transform>(), _e.GetComponent<Sprite>().color);
}

/*!*****************************************************************************
\brief
Creates a debug point based on Transform and Sprite Component, or Physics point
collider.

\param const Transform& _t
The transform component.

\param const Color& _c
The color component.
*******************************************************************************/
void RenderManager::CreateDebugPoint(const Transform& _t, const Color& _c)
{
	glm::vec4 clr = GetColor(_c.r, _c.g, _c.b, _c.a);
	Math::Mat3 mtx = GetTransform({ 0, 0 }, 0, _t.translation);

	Vertex v0;
	v0.color = clr;
	v0.position = (mtx * Math::Vec3(0, 0, 1.f)).ToGLM();
	v0.texID = 0.f;
	v0.position.z = 1;

	mDebugPoints.push_back(v0);
}

/*!*****************************************************************************
\brief
Creates a debug line based on Transform and Sprite Component, or Physics Edge
Collider.

\param const Entity& _e
The entity containing Transform and Sprite component.
*******************************************************************************/
void RenderManager::CreateDebugLine(const Entity& _e)
{
	CreateDebugLine(_e.GetComponent<Transform>(), _e.GetComponent<Sprite>().color);
}

/*!*****************************************************************************
\brief
Creates a debug line based on Transform and Sprite Component, or Physics Edge
Collider.

\param const Transform& _t
The transform component.

\param const Color& _c
The color component.
*******************************************************************************/
void RenderManager::CreateDebugLine(const Transform& _t, const Color& _c)
{
	glm::vec4 clr = GetColor(_c.r, _c.g, _c.b, _c.a);
	Math::Mat3 mtx = GetTransform(_t.scale, _t.rotation, _t.translation);

	Vertex v0, v1;
	v0.color = clr;
	v0.position = (mtx * Math::Vec3(0.f, 0.f, 1.f)).ToGLM();
	v0.position.z = 1;
	v0.texID = 0.f;

	v1.color = clr;
	v1.position = (mtx * Math::Vec3(1.f, 0.f, 1.f)).ToGLM();
	v1.position.z = 1;
	v1.texID = 0.f;

	mDebugVertices.push_back(v0);
	mDebugVertices.push_back(v1);

	GLushort first = mDebugIndices.empty() ? 0 : mDebugIndices.back() + 1;
	mDebugIndices.push_back(first);
	mDebugIndices.push_back(first + 1);
}

/*!*****************************************************************************
\brief
Creates a debug Square based on Transform and Sprite Component, or Physics Rect
Collider.

\param const Entity& _e
The entity containing Transform and Sprite component.
*******************************************************************************/
void RenderManager::CreateDebugSquare(const Entity& _e)
{
	CreateDebugSquare(_e.GetComponent<Transform>(), _e.GetComponent<Sprite>().color);
}

/*!*****************************************************************************
\brief
Creates a debug Square based on Transform and Sprite Component, or Physics Rect
Collider.

\param const Transform& _t
The transform component.

\param const Color& _c
The color component.
*******************************************************************************/
void RenderManager::CreateDebugSquare(const Transform& _t, const Color& _c)
{
	Math::Mat3 mtx = GetTransform(_t.scale, _t.rotation, _t.translation);
	glm::vec4 clr = GetColor(_c.r, _c.g, _c.b, _c.a);
	Vertex v0, v1, v2, v3;
	v0.position = (mtx * Math::Vec3(-1.f, 1.f, 1.f)).ToGLM();
	v0.position.z = 1;
	v0.color = clr;
	v0.texID = 0.f;

	v1.position = (mtx * Math::Vec3(-1.f, -1.f, 1.f)).ToGLM();
	v1.position.z = 1;
	v1.color = clr;
	v1.texID = 0.f;

	v2.position = (mtx * Math::Vec3(1.f, 1.f, 1.f)).ToGLM();
	v2.position.z = 1;
	v2.color = clr;
	v2.texID = 0.f;

	v3.position = (mtx * Math::Vec3(1.f, -1.f, 1.f)).ToGLM();
	v3.position.z = 1;
	v3.color = clr;
	v3.texID = 0.f;

	mDebugVertices.push_back(v0);
	mDebugVertices.push_back(v1);
	mDebugVertices.push_back(v3);
	mDebugVertices.push_back(v2);

	GLushort first = mDebugIndices.empty() ? 0 : mDebugIndices.back() + 1;
	mDebugIndices.push_back(first);
	mDebugIndices.push_back(first + 1);
	mDebugIndices.push_back(first + 1);
	mDebugIndices.push_back(first + 2);
	mDebugIndices.push_back(first + 2);
	mDebugIndices.push_back(first + 3);
	mDebugIndices.push_back(first);
	mDebugIndices.push_back(first + 3);
}

/*!*****************************************************************************
\brief
Creates a debug circle based on Transform and Sprite Component, or Physics Circle
Collider.

\param const Entity& _e
The entity containing Transform and Sprite component.
*******************************************************************************/
void RenderManager::CreateDebugCircle(const Entity& _e)
{
	CreateDebugCircle(_e.GetComponent<Transform>(), _e.GetComponent<Sprite>().color);
}

/*!*****************************************************************************
\brief
Creates a debug circle based on Transform and Sprite Component, or Physics Circle
Collider.

\param const Transform& _t
The transform component.

\param const Color& _c
The color component.
*******************************************************************************/
void RenderManager::CreateDebugCircle(const Transform& _t, const Color& _c)
{
	Math::Mat3 mtx = GetTransform(_t.scale, _t.rotation, _t.translation);
	glm::vec4 clr = GetColor(_c.r, _c.g, _c.b, _c.a);

	float theta = 2.f / CIRCLE_SLICES * 3.14159265f;

	for (int i = 1; i < CIRCLE_SLICES + 2; ++i)
	{
		Vertex v;
		v.position = (mtx * Math::Vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f)).ToGLM();
		v.position.z = 1;
		v.color = clr;
		v.texID = 0.f;
		mDebugVertices.push_back(v);
	}

	GLushort first = mDebugIndices.empty() ? 0 : mDebugIndices.back() + 1;

	for (GLushort i = 0; i < CIRCLE_SLICES; ++i)
	{
		mDebugIndices.push_back(first + i);
		mDebugIndices.push_back(first + i + 1);
	}
}

/*!*****************************************************************************
\brief
Creates a debug arrow based on Transform and Sprite Component, or Physics2D
component.

\param const Entity& _e
The entity containing Transform and Sprite component.
*******************************************************************************/
void RenderManager::CreateDebugArrow(const Entity& _e)
{
	CreateDebugLine(_e);
	mDebugPoints.push_back(mDebugVertices.back());
}

/*!*****************************************************************************
\brief
Creates a debug arrow based on Transform and Sprite Component, or Physics2D
component.

\param const Transform& _t
The transform component.

\param const Color& _c
The color component.
*******************************************************************************/
void RenderManager::CreateDebugArrow(const Transform& _t, const Color& _c)
{
	CreateDebugLine(_t, _c);
	mDebugPoints.push_back(mDebugVertices.back());
}

/*!*****************************************************************************
\brief
Sets the debug mode of rendering.

\param bool
Renders debug drawings if debug mode is set to true.
*******************************************************************************/
void RenderManager::SetDebug(bool _set)
{
	mDebug = _set;
}

/*!*****************************************************************************
\brief
Sets the modifier for the length of the debug vector.

\param float
Modifier for the length of the vector.
*******************************************************************************/
void RenderManager::SetVectorLengthModifier(float _modifier)
{
	mVectorLengthModifier = _modifier;
}

/*!*****************************************************************************
\brief
Helper function for returning the color of the Sprite Component in OpenGL.

\param const Entity& _e
The entity containing Transform and Sprite component.

\return
Returns the color of the Sprite.
*******************************************************************************/
glm::vec4 RenderManager::GetColor(const Entity& _e)
{
	return GetColor(_e.GetComponent<Sprite>().color.r, _e.GetComponent<Sprite>().color.g,
		_e.GetComponent<Sprite>().color.b, _e.GetComponent<Sprite>().color.a);
}

/*!*****************************************************************************
\brief
Helper function for returning a Color in OpenGL.

\param GLubyte _r
The redness of the color.

\param GLubyte _g
The greenness of the color.

\param GLubyte _b
The blueness of the color.

\param GLubyte _a
The transparency of the color.

\return
Returns the color.
*******************************************************************************/
glm::vec4 RenderManager::GetColor(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a)
{
	return { _r / 255.f, _g / 255.f, _b / 255.f, _a / 255.f };
}

/*!*****************************************************************************
\brief
Helper function for returning the Transformation matrix of a Component.

\param const Entity& _e
The entity containing Transform and Sprite component.

\return
The Transformation matrix.
*******************************************************************************/
Math::Mat3 RenderManager::GetTransform(const Entity& _e)
{
	return GetTransform(_e.GetComponent<Transform>().scale, _e.GetComponent<Transform>().rotation,
		_e.GetComponent<Transform>().translation);
}

/*!*****************************************************************************
\brief
Helper function for returning the Transformation matrix given scale, rotate, and
translate.

\param const Math::Vec2& _scale
The scale for the transformation.

\param float _rotate
The rotation for the transformation

\param const Math::Vec2& _translate
The translatetion for the transformation

\return
The Transformation matrix.
*******************************************************************************/
Math::Mat3 RenderManager::GetTransform(const Math::Vec2& _scale, float _rotate, const Math::Vec2& _translate)
{
	Camera cam = mCurrRenderPass == RENDER_STATE::GAME ? mGameCam : mWorldCam;
	float cosRot = cosf(_rotate);
	float sinRot = sinf(_rotate);

	Math::Mat3 temp
	{
		Math::Vec3(_scale.x * cosRot, _scale.x * sinRot, 0.f),
		Math::Vec3(-_scale.y * sinRot, _scale.y * cosRot, 0.f),
		Math::Vec3(_translate.x, _translate.y, 1.f)
	};

	temp[2][0] -= cam.GetPos().x;
	temp[2][1] -= cam.GetPos().y;

	temp[0][0] /= (float)*mWindowWidth * cam.GetZoom();
	temp[0][1] /= (float)*mWindowHeight * cam.GetZoom();
	temp[1][0] /= (float)*mWindowWidth * cam.GetZoom();
	temp[1][1] /= (float)*mWindowHeight * cam.GetZoom();
	temp[2][0] /= (float)*mWindowWidth / 2.f * cam.GetZoom();
	temp[2][1] /= (float)*mWindowHeight / 2.f * cam.GetZoom();

	return temp;
}

/*!*****************************************************************************
\brief
Initializes the Shader program.
*******************************************************************************/
void RenderManager::InitializeShaders()
{
	mDefaultProgram.CompileLinkShaders();
	mTextureProgram.CompileLinkShaders();

	mDefaultProgram.Validate(), mTextureProgram.Validate();
}

/*!*****************************************************************************
\brief
Helper function for concatenating the vector of indices.

\param std::vector<GLushort>& _first
The vector for indices to be pushed into.

\param std::vector<GLushort>& _second
The vector for indices to be taken from.
*******************************************************************************/
void RenderManager::ConcatIndices(std::vector<GLushort>& _first, std::vector<GLushort>& _second)
{
	if (_first.empty())
	{
		for (GLushort& idx : _second)
			_first.push_back(idx);
		return;
	}
	GLushort back = _first.back();
	for (GLushort idx : _second)
	{
		idx += back + 1;
		_first.push_back(idx);
	}
}
