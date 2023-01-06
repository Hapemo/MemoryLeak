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
#include "RenderProps.h"
#include "Input.h"
#include <ECSManager.h>
#include <VertexFetcher.h>
#include <GameStateManager.h>

/*!*****************************************************************************
\brief
Default Constructor for RenderManager class.
*******************************************************************************/
RenderManager::RenderManager()
	: mAllocator(NO_OF_OBJECTS, VERTICES_PER_OBJECT, INDICES_PER_OBJECT),
	mWorldFBO(), mGameFBO(), mAnimatorFBO(), 
	mDefaultProgram("shaders/default.vert", "shaders/default.frag"),
	mTextureProgram("shaders/texture.vert", "shaders/texture.frag"),
	/*mMinimapProgram("shaders/texture.vert", "shaders/minimap.frag"),*/
	mWindowHeight(nullptr), mWindowWidth(nullptr)/*, minimap(0)*/
{
	//render world (editor)
	mRenderGameToScreen = true;
	mCurrRenderPass = RENDER_STATE::GAME;
	mVectorLengthModifier = 10.f;

	//initialize opengl values
	glClearColor(0.537f, 0.812f, 0.941f, 0.f);
	glPointSize(8.f);
	glLineWidth(5.f);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitializeShaders();
	mDebug = false;
	mRenderLayers.reserve(255);
	mIsCurrSceneUI = false;
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
	mInitialWidth = *_windowWidth;
	mInitialHeight = *_windowHeight;
	//initialize fbo with window width and height
	mWorldFBO.Init(*mWindowWidth, *mWindowHeight);
	mGameFBO.Init(*mWindowWidth, *mWindowHeight);
	mAnimatorFBO.Init(*mWindowWidth, *mWindowHeight);
	mWorldCam.Init(*mWindowWidth, *mWindowHeight);
	mGameCam.Init(*mWindowWidth, *mWindowHeight);
	mAnimatorCam.Init(*mWindowWidth, *mWindowHeight);
	mPrevWidth = *mWindowWidth;
}

/*!*****************************************************************************
\brief
Render Entities with Sprite and Transform Component.
*******************************************************************************/
void RenderManager::Render()
{
	gs = GameStateManager::GetInstance()->mCurrentGameState;

	if (gs)
	{
		mGameCam.SetCameraWidth((int)reinterpret_cast<GameState*>(gs)->mCamera.scale.x);
		mGameCam.SetPos(reinterpret_cast<GameState*>(gs)->mCamera.translation);
		reinterpret_cast<GameState*>(gs)->mCamera.scale.y = mGameCam.GetCameraHeight();
		reinterpret_cast<GameState*>(gs)->mCamera.rotation = 1.f / mGameCam.GetZoom();
	}

	if (mPrevWidth != *mWindowWidth)
	{
		mPrevWidth = *mWindowWidth;
		mWorldFBO.DeleteFBO();
		mGameFBO.DeleteFBO();
		mAnimatorFBO.DeleteFBO();
		mWorldFBO.Init(*mWindowWidth, *mWindowHeight);
		mGameFBO.Init(*mWindowWidth, *mWindowHeight);
		mAnimatorFBO.Init(*mWindowWidth, *mWindowHeight);
	}
	if (!mRenderGameToScreen)
		mCurrRenderPass == RENDER_STATE::GAME ? 
		mGameFBO.Bind() : mWorldFBO.Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::map<size_t, std::map<GLuint, TextureInfo>> textureInfo;

	/*************************************CREATING VERTICES START************************************/
	//creating squares and circles based on Sprite component
	if (mCurrRenderPass == RENDER_STATE::WORLD && mGizmo.GetAttached().id != 0)
		mGizmo.Update(editorManager->GetEditorWorldMousePos(), mWorldCam);

	CreateVertices(textureInfo);
	/*************************************CREATING VERTICES END**************************************/

	BatchRenderLayers(textureInfo);

	//if rendering to editor OR debug mode is on and is rendering to screen, then render debug
	if (mCurrRenderPass == RENDER_STATE::WORLD || mDebug)
		RenderDebug();

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
	for (auto itr = mFontRenderers.begin(); itr != mFontRenderers.end(); ++itr)
		itr->second.Clear();


	//recursion for editor viewport
	if (mCurrRenderPass == RENDER_STATE::WORLD)
		Render();
	//minimap.id = 0;
}

/*!*****************************************************************************
\brief
Returns the color attachment to the Animator buffer, for displaying the
Animator editor.

\return
Returns the color attachment to the Animator buffer, for displaying the
Animator editor.
*******************************************************************************/
GLuint RenderManager::GetAnimatorFBO()
{
	RENDER_STATE prevState = mCurrRenderPass;
	mCurrRenderPass = RENDER_STATE::ANIMATOR;
	mAnimatorFBO.Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::map<size_t, std::map<GLuint, TextureInfo>> textureInfo;

	CreateVertices(textureInfo);
	BatchRenderLayers(textureInfo);

	mAnimatorFBO.Unbind();

	//clear vertices for next iteration
	mVertices.clear();
	mIndices.clear();
	mTextureVertices.clear();
	mTextureIndices.clear();
	mDebugPoints.clear();
	mDebugVertices.clear();
	mDebugIndices.clear();
	mCurrRenderPass = prevState;

	return mAnimatorFBO.GetColorAttachment();
}

void RenderManager::BatchRenderLayers(std::map<size_t, std::map<GLuint, TextureInfo>>& _texinfo)
{
	for (int layer : mRenderLayers)
	{
		if (_texinfo.find(layer) != _texinfo.end())
			RenderTextures(_texinfo[layer]);
		RenderShapes(layer);
		RenderText(layer);
	}
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
	//use normal program for drawing shapes
	mDefaultProgram.Bind();
	mAllocator.BindVAO();

	//overlay for game camera to see where it is
	if (mCurrRenderPass == RENDER_STATE::WORLD)
	{
		Color blue{ 255,0,0,100 };
		Transform t;
		t.rotation = 0;
		t.scale = mGameCam.GetZoom() * mGameCam.GetWindowDim();
		t.translation = mGameCam.GetPos();
		CreateDebugSquare(t, blue);
		CreateDebugLine(t, blue);
		t.rotation += (float)Math::PI / 2.f;
		t.scale = { t.scale.y, t.scale.x };
		CreateDebugLine(t, blue);
		t.rotation += (float)Math::PI / 2.f;
		t.scale = { t.scale.y, t.scale.x };
		CreateDebugLine(t, blue);
		t.rotation += (float)Math::PI / 2.f;
		t.scale = { t.scale.y, t.scale.x };
		CreateDebugLine(t, blue);
	}
	for (const Scene& scene : reinterpret_cast<GameState*>(gs)->mScenes)
	{
		if (scene.mIsPause) continue;

		if (scene.mIsUI && mCurrRenderPass != RENDER_STATE::WORLD)
			mIsCurrSceneUI = true;
		else
			mIsCurrSceneUI = false;

		for (Entity e : scene.mEntities)
		{
			if (!e.GetComponent<General>().isActive) continue;
			if (!e.ShouldRun()) continue;

			//check if entity has any of these physics components
			if (e.HasComponent<Point2DCollider>() && e.GetComponent<Point2DCollider>().renderFlag)
			{
				Transform t = e.GetComponent<Transform>();
				t.scale = { 0, 0 };
				t.rotation = 0;
				t.translation += Math::Vec2(e.GetComponent<Point2DCollider>().centerOffset.x,
					e.GetComponent<Point2DCollider>().centerOffset.y);
				CreateDebugSquare(t, { 0, 255, 0, 255 });
			}

			if (e.HasComponent<Edge2DCollider>() && e.GetComponent<Edge2DCollider>().renderFlag)
			{
				Transform t = e.GetComponent<Transform>();
				t.scale = { e.GetComponent<Edge2DCollider>().scaleOffset };
				t.rotation += e.GetComponent<Edge2DCollider>().rotationOffset;
				t.translation += Math::Vec2(e.GetComponent<Edge2DCollider>().p0Offset.x,
					e.GetComponent<Edge2DCollider>().p0Offset.y);
				CreateDebugLine(t, { 0, 255, 0, 255 });
			}

			if (e.HasComponent<RectCollider>() && e.GetComponent<RectCollider>().renderFlag)
			{
				Transform t = e.GetComponent<Transform>();
				t.scale.x *= e.GetComponent<RectCollider>().scaleOffset.x;
				t.scale.y *= e.GetComponent<RectCollider>().scaleOffset.y;
				t.rotation = 0;
				t.translation += Math::Vec2(e.GetComponent<RectCollider>().centerOffset.x,
					e.GetComponent<RectCollider>().centerOffset.y);
				CreateDebugSquare(t, { 0, 255, 0, 255 });
			}

			if (e.HasComponent<LayerCollider>() && e.GetComponent<LayerCollider>().renderFlag)
			{
				Transform t = e.GetComponent<Transform>();
				t.scale.x *= e.GetComponent<LayerCollider>().scaleOffset.x;
				t.scale.y *= e.GetComponent<LayerCollider>().scaleOffset.y;
				t.rotation = 0;
				t.translation += Math::Vec2(e.GetComponent<LayerCollider>().centerOffset.x,
					e.GetComponent<LayerCollider>().centerOffset.y);
				CreateDebugSquare(t, { 255, 150, 0, 255 });
			}

			if (e.HasComponent<CircleCollider>() && e.GetComponent<CircleCollider>().renderFlag)
			{
				Transform t = e.GetComponent<Transform>();
				t.scale = Math::Vec2(std::max(t.scale.x, t.scale.y) * e.GetComponent<CircleCollider>().scaleOffset);
				t.rotation = 0;
				t.translation += Math::Vec2(e.GetComponent<CircleCollider>().centerOffset.x,
					e.GetComponent<CircleCollider>().centerOffset.y);
				CreateDebugCircle(t, { 0,255,0,255 });
			}

			if (e.HasComponent<Physics2D>() && e.GetComponent<Physics2D>().renderFlag)
			{
				Physics2D& p2d = e.GetComponent<Physics2D>();
				Transform t = e.GetComponent<Transform>();
				t.scale = Math::Vec2(p2d.velocity.Magnitude()) * mVectorLengthModifier;
				if (p2d.velocity.y != 0.f && p2d.velocity.x >= 0.f)
					t.rotation = atan2f(p2d.velocity.y, p2d.velocity.x);
				else if (p2d.velocity.y == 0.f && p2d.velocity.x > 0.f)
					t.rotation = (float)Math::PI / 2.f;
				else if (p2d.velocity.y != 0.f && p2d.velocity.x < 0.f)
					t.rotation = (float)Math::PI * 2.f + atan2f(p2d.velocity.y, p2d.velocity.x);
				else
					t.rotation = 3.f * (float)Math::PI / 2.f;
				CreateDebugArrow(t, { 0, 255, 0, 255 });
			}

			//check if sprite component itself is a debug drawing
			if (!e.HasComponent<Sprite>()) continue;
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
	}


	//make overlay for selected entities in the editor
	for (const Entity& e : mEditorSelectedEntities)
	{
		if (!e.HasComponent<General>()) continue;
		if (!e.GetComponent<General>().isActive) continue;
		if (!e.ShouldRun()) continue;

		Color blue{ 0,0,255,100 };
		Transform xform = e.GetComponent<Transform>();
		CreateDebugSquare(xform, blue);
		CreateDebugLine(xform, blue);
		xform.rotation += (float)Math::PI / 2.f;
		xform.scale = { xform.scale.y, xform.scale.x };
		CreateDebugLine(xform, blue);
		xform.rotation += (float)Math::PI / 2.f;
		xform.scale = { xform.scale.y, xform.scale.x };
		CreateDebugLine(xform, blue);
		xform.rotation += (float)Math::PI / 2.f;
		xform.scale = { xform.scale.y, xform.scale.x };
		CreateDebugLine(xform, blue);
	}

	/***************************************DEBUG BATCHING START*************************************/
	BatchRenderArrays(GL_POINTS, mDebugPoints);
	BatchRenderElements(GL_LINES, mDebugVertices, mDebugIndices);
	/***************************************DEBUG BATCHING END***************************************/
	//unuse VAO and normal program
	mAllocator.UnbindVAO();
	mDefaultProgram.Unbind();
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
Creating vertices from the ECS.
*******************************************************************************/
void RenderManager::CreateVertices(std::map<size_t, std::map<GLuint, TextureInfo>>&_texInfo)
{
	for (const Scene& scene : reinterpret_cast<GameState*>(gs)->mScenes)
	{
		if (scene.mIsPause) continue;

		if (scene.mIsUI)
			mIsCurrSceneUI = true;
		else
			mIsCurrSceneUI = false;

		for (Entity e : scene.mEntities)
		{
			if (!e.GetComponent<General>().isActive) continue;
			if (!e.ShouldRun()) continue;
			if (ShouldCull(e)) continue;

			if (e.HasComponent<Sprite>())
			{
				//if (e.GetComponent<General>().name == "Minimap")
				//{
				//	minimap = e;
				//	continue;
				//}
				Sprite sprite = e.GetComponent<Sprite>();
				if (find(mRenderLayers.begin(), mRenderLayers.end(), sprite.layer) == mRenderLayers.end())
					mRenderLayers.push_back(sprite.layer);

				switch (sprite.sprite)
				{
				case SPRITE::TEXTURE:
				{
					GLuint texid = sprite.texture;

					if (texid != 0)
					{
						if (_texInfo.find(sprite.layer) == _texInfo.end())
							_texInfo[sprite.layer] = std::map<GLuint, TextureInfo>();
						if (_texInfo[sprite.layer].find(texid) == _texInfo[sprite.layer].end())
							_texInfo[sprite.layer][texid] = { (int)texid - 1, std::vector<Vertex>(), std::vector<GLushort>() };

						CreateSquare(e, _texInfo[sprite.layer][texid].mVertices, _texInfo[sprite.layer][texid].mIndices);
					}
				}
				break;
				case SPRITE::SQUARE:
					CreateSquare(e, mVertices[sprite.layer], mIndices[sprite.layer]);
					break;
				case SPRITE::CIRCLE:
					CreateCircle(e);
					break;
				default:
					break;
				}
			}

			if (!e.HasComponent<Text>()) continue;
			CreateText(e);
		}
	}
	if (mCurrRenderPass == RENDER_STATE::WORLD)
		CreateGizmo();

	std::sort(mRenderLayers.begin(), mRenderLayers.end());
}

/*!*****************************************************************************
\brief
Rendering of textures
*******************************************************************************/
void RenderManager::RenderTextures(std::map<GLuint, TextureInfo>&_texInfo)
{
	int samplerUniform[TEXTURES_PER_DRAW];
	for (int i = 0; i < TEXTURES_PER_DRAW; ++i)
		samplerUniform[i] = i;
	//use texture program and bind VAO
	mTextureProgram.Bind();
	mAllocator.BindVAO();

	//insert uniforms
	mTextureProgram.InsertUniform1iv("uTex2D", TEXTURES_PER_DRAW, samplerUniform);

	int textureCount = 0;

	std::vector<int> usedTexUnits;
	usedTexUnits.reserve(TEXTURES_PER_DRAW);

	//iterate over texture map
	for (std::map<GLuint, TextureInfo>::iterator it = _texInfo.begin(); it != _texInfo.end(); ++it)
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

	//creating minimap image
	//if (minimap.id != 0)
	//{
	//	std::vector<Vertex> minimapVertex;
	//	std::vector<GLushort> minimapIndices;
	//	CreateSquare(minimap, minimapVertex, minimapIndices);
	//	TextureInfo minimapInfo{ (int)minimap.GetComponent<Sprite>().texture - 1, minimapVertex, minimapIndices };
	//	int samplerUniform1[TEXTURES_PER_DRAW];
	//	for (int i = 0; i < TEXTURES_PER_DRAW; ++i)
	//		samplerUniform1[i] = i;
	//	//use texture program and bind VAO
	//	mMinimapProgram.Bind();
	//	mAllocator.BindVAO();
	//	mTextureProgram.InsertUniform1iv("uTex2D", TEXTURES_PER_DRAW, samplerUniform1);
	//	std::vector<int> usedTexUnits1;
	//	usedTexUnits1.reserve(TEXTURES_PER_DRAW);
	//	BindTextureUnit(minimap.GetComponent<Sprite>().texture, minimapInfo, usedTexUnits1);
	//	int texcount = 1;
	//	BatchRenderTextures(texcount, usedTexUnits1);
	//	mAllocator.UnbindVAO();
	//	mMinimapProgram.Unbind();
	//}
}

/*!*****************************************************************************
\brief
Rendering of shapes
*******************************************************************************/
void RenderManager::RenderShapes(int _layer)
{
	if (mVertices.find(_layer) == mVertices.end()) return;

	//use normal program for drawing shapes
	mDefaultProgram.Bind();
	mAllocator.BindVAO();

	//render all shapes
	BatchRenderElements(GL_TRIANGLES, mVertices[_layer], mIndices[_layer]);

	//unuse VAO and normal program
	mAllocator.UnbindVAO();
	mDefaultProgram.Unbind();
}

void RenderManager::RenderText(int _layer)
{
	Camera currCam = mCurrRenderPass == RENDER_STATE::WORLD ? mWorldCam
		: mCurrRenderPass == RENDER_STATE::GAME ? mGameCam : mAnimatorCam;
	for (auto i = mFontRenderers.begin(); i != mFontRenderers.end(); ++i)
		if (i->second.IsInitialized())
		{
			i->second.SetCamZoom(currCam.GetZoom());
			i->second.DrawParagraphs(_layer);
		}
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
Resets all the cameras in RenderManager.
*******************************************************************************/
void RenderManager::ResetCameras()
{
	mAnimatorCam.Reset();
	mGameCam.Reset();
	mWorldCam.Reset();
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
	CreateCircle(_e.GetComponent<Transform>(), _e.GetComponent<Sprite>().color, 
		_e.GetComponent<Sprite>().layer);
}

/*!*****************************************************************************
\brief
Creates a circle based on Transform, Color and layer.

\param const Transform& _t
The transform component.

\param const Color& _cltr&
The color component.

\param float
layer to render at.
*******************************************************************************/
void RenderManager::CreateCircle(const Transform& _xform, const Color& _clr, int _layer)
{
	Math::Mat3 mtx = GetTransform(_xform.scale, _xform.rotation, _xform.translation);
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };
	float layer = (_layer * 2 - 255) / 255.f;

	float theta = 2.f / CIRCLE_SLICES * 3.14159265f;
	Vertex v0;
	v0.position = (mtx * Math::Vec3(0.f, 0.f, 1.f)).ToGLM();
	v0.position.z = layer;
	v0.color = clr;
	v0.texID = 0.f;
	mVertices[_layer].push_back(v0);

	for (int i = 1; i < CIRCLE_SLICES + 2; ++i)
	{
		Vertex v;
		v.position = (mtx * Math::Vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f)).ToGLM();
		v.position.z = layer;
		v.color = clr;
		v.texID = 0.f;
		mVertices[_layer].push_back(v);
	}

	GLushort pivot = mIndices[_layer].empty() ? 0 : mIndices[_layer].back() + 1;

	for (GLushort i = 0; i < CIRCLE_SLICES; ++i)
	{
		mIndices[_layer].push_back(pivot);
		mIndices[_layer].push_back(pivot + 1 + i);
		mIndices[_layer].push_back(pivot + 2 + i);
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
	CreateDebugPoint(_e.GetComponent<Transform>(), {0, 255, 0, 255});
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
void RenderManager::CreateDebugPoint(const Transform& _t, const Color& _clr)
{
	glm::vec4 clr{ _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };
	Math::Mat3 mtx = GetTransform({ 0, 0 }, 0, _t.translation);

	Vertex v0;
	v0.color = clr;
	v0.position = (mtx * Math::Vec3(0, 0, 1.f)).ToGLM();
	v0.texID = 0.f;
	v0.position.z = 0.99f;

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
	CreateDebugLine(_e.GetComponent<Transform>(), {0, 255, 0, 255});
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
void RenderManager::CreateDebugLine(const Transform& _t, const Color& _clr)
{
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };
	Math::Mat3 mtx = GetTransform(_t.scale, _t.rotation, _t.translation);

	Vertex v0, v1;
	v0.color = clr;
	v0.position = (mtx * Math::Vec3(0.f, 0.f, 1.f)).ToGLM();
	v0.position.z = 0.99f;
	v0.texID = 0.f;

	v1.color = clr;
	v1.position = (mtx * Math::Vec3(1.f, 0.f, 1.f)).ToGLM();
	v1.position.z = 0.99f;
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
	CreateDebugSquare(_e.GetComponent<Transform>(), {0, 255, 0, 255});
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
void RenderManager::CreateDebugSquare(const Transform& _t, const Color& _clr)
{
	Math::Mat3 mtx = GetTransform(_t.scale, _t.rotation, _t.translation);
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };
	Vertex v0, v1, v2, v3;
	v0.position = (mtx * Math::Vec3(-1.f, 1.f, 1.f)).ToGLM();
	v0.position.z = 0.95f;
	v0.color = clr;
	v0.texID = 0.f;

	v1.position = (mtx * Math::Vec3(-1.f, -1.f, 1.f)).ToGLM();
	v1.position.z = 0.95f;
	v1.color = clr;
	v1.texID = 0.f;

	v2.position = (mtx * Math::Vec3(1.f, 1.f, 1.f)).ToGLM();
	v2.position.z = 0.95f;
	v2.color = clr;
	v2.texID = 0.f;

	v3.position = (mtx * Math::Vec3(1.f, -1.f, 1.f)).ToGLM();
	v3.position.z = 0.95f;
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
	CreateDebugCircle(_e.GetComponent<Transform>(), {0, 255, 0, 255});
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
void RenderManager::CreateDebugCircle(const Transform& _t, const Color& _clr)
{
	Math::Mat3 mtx = GetTransform(_t.scale, _t.rotation, _t.translation);
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };

	float theta = 2.f / CIRCLE_SLICES * static_cast<float>(Math::PI);

	for (int i = 1; i < CIRCLE_SLICES + 2; ++i)
	{
		Vertex v;
		v.position = (mtx * Math::Vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f)).ToGLM();
		v.position.z = 0.99f;
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
void RenderManager::CreateDebugArrow(const Transform& _t, const Color& _clr)
{
	CreateDebugLine(_t, _clr);
	mDebugPoints.push_back(mDebugVertices.back());
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
	Camera cam = mCurrRenderPass == RENDER_STATE::GAME ? 
		mGameCam : 
		mCurrRenderPass == RENDER_STATE::WORLD ? 
		mWorldCam : mAnimatorCam;
	float cosRot = cosf(_rotate);
	float sinRot = sinf(_rotate);

	Math::Vec2 camPos = mIsCurrSceneUI ? Math::Vec2{0, 0} : cam.GetPos();
	float camZoom = mIsCurrSceneUI ? 1.f : cam.GetZoom();

	Math::Mat3 temp
	{
		Math::Vec3(_scale.x * cosRot, _scale.x * sinRot, 0.f),
		Math::Vec3(-_scale.y * sinRot, _scale.y * cosRot, 0.f),
		Math::Vec3(_translate.x, _translate.y, 1.f)
	};

	temp[2][0] -= camPos.x;
	temp[2][1] -= camPos.y;

	temp[0][0] /= (float)mInitialWidth* camZoom;
	temp[0][1] /= (float)mInitialHeight* camZoom;
	temp[1][0] /= (float)mInitialWidth* camZoom;
	temp[1][1] /= (float)mInitialHeight* camZoom;
	temp[2][0] /= (float)mInitialWidth/ 2.f * camZoom;
	temp[2][1] /= (float)mInitialHeight/ 2.f * camZoom;

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
	//mMinimapProgram.CompileLinkShaders();

	mDefaultProgram.Validate();
	mTextureProgram.Validate();
	//mMinimapProgram.Validate();
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
/*!*****************************************************************************
\brief
Sets the color to be cleared every frame.

\param const Color& _clr
The color to be cleared with.
*******************************************************************************/
void RenderManager::SetClearColor(const Color& _clr)
{
	glClearColor(_clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f);
}
/*!*****************************************************************************
\brief
Sends text into the FontManager to be rendered.

\param const Entity& _e
The entity with the Text component.
*******************************************************************************/
void RenderManager::CreateText(const Entity& _e)
{
	static bool debug{ false };
	Text text = _e.GetComponent<Text>();

	std::string fileName = text.fontFile + ".ttf";

	//check if font program already exisits, if not create one
	if (mFontRenderers.find(fileName) == mFontRenderers.end())
	{
		mFontRenderers.emplace(fileName, fileName);
		mFontRenderers[fileName].SetWindowPtr(mWindowWidth, mWindowHeight);
	}

	//add paragraph into font renderer
	if (!mFontRenderers[fileName].IsInitialized())
		return;

	Math::Vec2 camOffset = { 0,0 };
	float camZoom = 1.f;
	if (!text.followCam)
	{
		camOffset = mCurrRenderPass == RENDER_STATE::WORLD ? mWorldCam.GetPos()
		: mCurrRenderPass == RENDER_STATE::GAME ? mGameCam.GetPos() : mAnimatorCam.GetPos();
		camZoom = mCurrRenderPass == RENDER_STATE::WORLD ? mWorldCam.GetZoom()
			: mCurrRenderPass == RENDER_STATE::GAME ? mGameCam.GetZoom() : mAnimatorCam.GetZoom();
	}

	int layer = 255;
	if (!_e.HasComponent<Sprite>())
	{
		if (!debug)
		{
			LOG_ERROR("FontRenderer: Component does not contain sprite component! Text will be rendered at max layer!");
			debug = !debug;
		}
	}
	else
		layer = _e.GetComponent<Sprite>().layer;
				
	mFontRenderers[fileName].AddParagraph(text.text,
		(text.offset + _e.GetComponent<Transform>().translation  - camOffset ) / camZoom + Math::Vec2(mInitialWidth * 0.5f, mInitialHeight * 0.5f),
		text.scale / camZoom, Math::Vec3(text.color.r / 255.f, text.color.g / 255.f, text.color.b / 255.f), layer, _e.GetComponent<Transform>().scale.x);
}

/*!*****************************************************************************
\brief
Creates the gizmo.
*******************************************************************************/
void RenderManager::CreateGizmo()
{
	if (!mGizmo.GetAttached().id)
		return;
	
	Color red{ 214, 53, 4, 255 };
	Color green{ 98, 250, 77, 255 };
	Color blue{ 45, 183, 247, 255 };
	Color purple{ 246, 45, 241, 255 };
	Transform entityTransform = mGizmo.GetAttached().GetComponent<Transform>();

	//drawing outer rotate circle
	Math::Vec2 translate = entityTransform.translation;
	Math::Vec2 scale{ GIZMO_CIRCLE_SIZE, GIZMO_CIRCLE_SIZE};
	Transform xform{ scale, 0.f, translate };
	CreateGizmoDebugCircle(xform, purple);

	//drawing scale x line
	xform.scale = GIZMO_LINE_SIZE;
	xform.rotation = 0.f;
	CreateGizmoDebugLine(xform, red);

	//drawing scale y line
	xform.rotation += (float)Math::PI / 2.f;
	CreateGizmoDebugLine(xform,green);

	//drawing scale x button
	Math::Vec2 prevScale = xform.scale;
	xform.translation += Math::Vec2{prevScale.x / 2.f, 0.f} * mWorldCam.GetZoom();
	xform.scale = GIZMO_BUTTON_SIZE;
	CreateGizmoCircle(xform, red);

	//drawing scale y button
	xform.translation += (Math::Vec2{0.f,  prevScale.x / 2.f}  - Math::Vec2{prevScale.x / 2.f, 0.f}) * mWorldCam.GetZoom();
	CreateGizmoCircle(xform, green);

	//drawing translate button
	xform.translation -= Math::Vec2{ 0.f, prevScale.x / 2.f } * mWorldCam.GetZoom();
	CreateGizmoCircle(xform, blue);

	//drawing rotate button
	translate += (Math::Vec2(cosf(entityTransform.rotation + (float)Math::PI / 2.f), 
		sinf(entityTransform.rotation + (float)Math::PI / 2.f)) * GIZMO_CIRCLE_SIZE / 2.f) * mWorldCam.GetZoom();
	xform.translation = translate;
	CreateGizmoCircle(xform, purple);
}

/*!*****************************************************************************
\brief
Used when an entity is selected in the editor. Draws a box around the selected
entity.

\param const Entity& _e
The entity to be selected.
*******************************************************************************/
void RenderManager::SelectEntity(const Entity& _e)
{
	ClearSelectedEntities();
	mEditorSelectedEntities.push_back(_e);
}
/*!*****************************************************************************
\brief
Select multiple entities.

\param std::vector<Entity>const& _es
The vector of entities to be selected.
*******************************************************************************/
void RenderManager::SelectEntities(std::vector<Entity>const& _es)
{
	mEditorSelectedEntities = _es;
}
/*!*****************************************************************************
\brief
Unselect an entity. (not drawing box around it)

\param const Entity& _e
The entity to be unselected.
*******************************************************************************/
void RenderManager::UnselectEntity(const Entity& _e)
{
	for (size_t i = 0; i < mEditorSelectedEntities.size(); ++i)
		if (mEditorSelectedEntities[i].id == _e.id)
		{
			mEditorSelectedEntities.erase(mEditorSelectedEntities.begin() + i);
			return;
		}
}
/*!*****************************************************************************
\brief
Unselect all entities. (nothing selected)
*******************************************************************************/
void RenderManager::ClearSelectedEntities()
{
	mEditorSelectedEntities.clear();
}

/*!*****************************************************************************
\brief
Get the transform for where to render the gizmo.

\param const Transform& _xform
The transform for the object.

\return
The transform matrix.
*******************************************************************************/
Math::Mat3 RenderManager::GetGizmoTransform(const Transform& _xform)
{
	float cosRot = cosf(_xform.rotation);
	float sinRot = sinf(_xform.rotation);

	Math::Mat3 temp
	{
		Math::Vec3(_xform.scale.x * cosRot, _xform.scale.x * sinRot, 0.f),
		Math::Vec3(-_xform.scale.y * sinRot, _xform.scale.y * cosRot, 0.f),
		Math::Vec3(_xform.translation.x, _xform.translation.y, 1.f)
	};


	temp[2][0] -= mWorldCam.GetPos().x;
	temp[2][1] -= mWorldCam.GetPos().y;

	temp[0][0] /= (float)mInitialWidth;
	temp[0][1] /= (float)mInitialHeight;
	temp[1][0] /= (float)mInitialWidth;
	temp[1][1] /= (float)mInitialHeight;
	temp[2][0] /= (float)mInitialWidth / 2.f * mWorldCam.GetZoom();
	temp[2][1] /= (float)mInitialHeight / 2.f * mWorldCam.GetZoom();

	return temp;
}

/*!*****************************************************************************
\brief
Creates a circle for the gizmo.

\param const Transform& _t
The transform for the circle.

\const Color& _clr
The color of the circle.
*******************************************************************************/
void RenderManager::CreateGizmoCircle(const Transform& _t, const Color& _clr)
{
	Math::Mat3 mtx = GetGizmoTransform(_t);
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };

	float theta = 2.f / CIRCLE_SLICES * 3.14159265f;
	Vertex v0;
	v0.position = (mtx * Math::Vec3(0.f, 0.f, 1.f)).ToGLM();
	v0.position.z = 1.f;
	v0.color = clr;
	v0.texID = 0.f;
	mVertices[255].push_back(v0);

	for (int i = 1; i < CIRCLE_SLICES + 2; ++i)
	{
		Vertex v;
		v.position = (mtx * Math::Vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f)).ToGLM();
		v.position.z = 1.f;
		v.color = clr;
		v.texID = 0.f;
		mVertices[255].push_back(v);
	}

	GLushort pivot = mIndices[255].empty() ? 0 : mIndices[255].back() + 1;

	for (GLushort i = 0; i < CIRCLE_SLICES; ++i)
	{
		mIndices[255].push_back(pivot);
		mIndices[255].push_back(pivot + 1 + i);
		mIndices[255].push_back(pivot + 2 + i);
	}
}

/*!*****************************************************************************
\brief
Creates a line for the gizmo.

\param const Transform& _t
The transform for the circle.

\const Color& _clr
The color of the circle.
*******************************************************************************/
void RenderManager::CreateGizmoDebugLine(const Transform& _t, const Color& _clr)
{
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };
	Math::Mat3 mtx = GetGizmoTransform(_t);

	Vertex v0, v1;
	v0.color = clr;
	v0.position = (mtx * Math::Vec3(0.f, 0.f, 1.f)).ToGLM();
	v0.position.z = 0.99f;
	v0.texID = 0.f;

	v1.color = clr;
	v1.position = (mtx * Math::Vec3(1.f, 0.f, 1.f)).ToGLM();
	v1.position.z = 0.99f;
	v1.texID = 0.f;

	mDebugVertices.push_back(v0);
	mDebugVertices.push_back(v1);

	GLushort first = mDebugIndices.empty() ? 0 : mDebugIndices.back() + 1;
	mDebugIndices.push_back(first);
	mDebugIndices.push_back(first + 1);
}

/*!*****************************************************************************
\brief
Creates a debug circle for the gizmo. (outline only)

\param const Transform& _t
The transform for the circle.

\const Color& _clr
The color of the circle.
*******************************************************************************/
void RenderManager::CreateGizmoDebugCircle(const Transform& _t, const Color& _clr)
{
	Math::Mat3 mtx = GetGizmoTransform(_t);
	glm::vec4 clr = { _clr.r / 255.f, _clr.g / 255.f, _clr.b / 255.f, _clr.a / 255.f };

	float theta = 2.f / CIRCLE_SLICES * static_cast<float>(Math::PI);

	for (int i = 1; i < CIRCLE_SLICES + 2; ++i)
	{
		Vertex v;
		v.position = (mtx * Math::Vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f)).ToGLM();
		v.position.z = 0.99f;
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
Checks if entity should be rendered.

\param const Entity& e

\return bool
true if it should be culled, false otherwise.
*******************************************************************************/
bool RenderManager::ShouldCull(const Entity& _e)
{
	if (!_e.HasComponent<Sprite>()) return false;
	if (mCurrRenderPass == RENDER_STATE::ANIMATOR) return false;
	Transform xform = _e.GetComponent<Transform>();
	Sprite sprite = _e.GetComponent<Sprite>();
	Camera cam = mCurrRenderPass == RENDER_STATE::WORLD ? mWorldCam : mGameCam;

	Math::Vec2 camDim = Math::Vec2(cam.GetCameraWidth(), cam.GetCameraHeight()) / 2;
	Math::Vec2 camMin = cam.GetPos() - camDim;
	Math::Vec2 camMax = cam.GetPos() + camDim;

	if (xform.translation.x >= camMin.x && xform.translation.y >= camMin.y)
		if (xform.translation.x <= camMax.x && xform.translation.y <= camMin.y)
			return false;

	switch (sprite.sprite)
	{
	case (SPRITE::SQUARE):
	case (SPRITE::TEXTURE):
	{
		std::vector<Math::Vec2> vertices = VertexFetcher::FetchVertices(_e);

		Math::Vec2 boxMin{}, boxMax{};

		for (size_t i = 0; i < vertices.size(); ++i)
		{
			if (!i)
			{
				boxMin = boxMax = vertices[i];
				continue;
			}
			if (vertices[i].x < boxMin.x)
				boxMin.x = vertices[i].x;
			if (vertices[i].y < boxMin.y)
				boxMin.y = vertices[i].y;
			if (vertices[i].x > boxMax.x)
				boxMax.x = vertices[i].x;
			if (vertices[i].y > boxMax.y)
				boxMax.y = vertices[i].y;
		}

		if (boxMax.x < camMin.x)
			return true;
		if (boxMin.x > camMax.x)
			return true;
		if (boxMax.y < camMin.y)
			return true;
		if (boxMin.y > camMax.y)
			return true;
		return false;
	}
	case (SPRITE::CIRCLE):
	{
		Math::Vec2 circleMin{}, circleMax{};
		float max_scale = std::max(xform.scale.x, xform.scale.y);
		Math::Vec2 scale = Math::Vec2(max_scale, max_scale) * 0.5f;
		circleMin = xform.translation - scale;
		circleMax = xform.translation + scale;

		if (circleMax.x < camMin.x)
			return true;
		if (circleMin.x > camMax.x)
			return true;
		if (circleMax.y < camMin.y)
			return true;
		if (circleMin.y > camMax.y)
			return true;
		return false;
	}
	default:
		return false;
	}
	return false;
}