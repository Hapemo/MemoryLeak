#include "RenderManager.h"
#include "pch.h"

constexpr int circle_slices = 12;
constexpr size_t no_of_objects = 10000;
constexpr size_t max_vertices_per_object = 4;
constexpr size_t indices_per_object = 6;
constexpr size_t max_textures_per_draw = 16;
constexpr float alpha = 0.25f;

RenderManager::RenderManager()
	: allocator(no_of_objects, max_vertices_per_object, indices_per_object),
	fbo(), textureProgram("shaders/batch.vert", "shaders/batch.frag")
{
	debug = true;
	vectorLengthModifier = 50.f;
	glClearColor(0.537f, 0.812f, 0.941f, 1.f);
	glPointSize(8.f);
	glLineWidth(2.f);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	InitializeShaders();
	vertices.reserve(no_of_objects * 0.1f * max_vertices_per_object);
	indices.reserve(no_of_objects * 0.1f * indices_per_object);
	textureVertices.reserve(no_of_objects * 0.2f * max_vertices_per_object);
	textureIndices.reserve(no_of_objects * 0.2f * indices_per_object);
	debugPoints.reserve(no_of_objects * 0.1f);
	debugVertices.reserve(no_of_objects * 0.1f * max_vertices_per_object);
	debugIndices.reserve(no_of_objects * 0.1f * indices_per_object);

}

void RenderManager::Render()
{
	if (!fbo.GetRenderToScreen())
		fbo.Bind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::map<GLuint, TextureInfo> textureInfo;
	int texUnit = 0;
	int samplerUniform[max_textures_per_draw];
	for (int i = 0; i < max_textures_per_draw; ++i)
		samplerUniform[i] = i;

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

				TRACK_PERFORMANCE("CreateSquare");
				CreateSquare(e, textureInfo[texid].vertices, textureInfo[texid].indices);
				END_TRACK("CreateSquare");
			}
		}
		break;
		case SPRITE::SQUARE:
			CreateSquare(e, vertices, indices);
			break;
		case SPRITE::CIRCLE:
			CreateCircle(e);
			break;
		default:
			continue;
		}
	}
	textureProgram.Bind();
	allocator.BindVAO();

	textureProgram.InsertUniform1iv("uTex2D", max_textures_per_draw, samplerUniform);

	int textureCount = 0;

	std::vector<int> usedTexUnits;
	usedTexUnits.reserve(max_textures_per_draw);

	for (std::map<GLuint, TextureInfo>::iterator it = textureInfo.begin(); it != textureInfo.end(); ++it)
	{
		if (std::find(usedTexUnits.begin(), usedTexUnits.end(), it->second.textureUnit % max_textures_per_draw) == usedTexUnits.end())
		{
			glBindTextureUnit(it->second.textureUnit % max_textures_per_draw, it->first);
			usedTexUnits.push_back(it->second.textureUnit % max_textures_per_draw);
			textureVertices.insert(textureVertices.end(), it->second.vertices.begin(), it->second.vertices.end());
			ConcatIndices(textureIndices, it->second.indices);
			++textureCount;
			if (textureCount == max_textures_per_draw)
			{
				textureCount = 0;
				BatchRenderElements(GL_TRIANGLES, textureVertices, textureIndices);
				textureVertices.clear();
				textureIndices.clear();
				usedTexUnits.clear();
			}
		}
		else
		{
			textureCount = 0;
			BatchRenderElements(GL_TRIANGLES, textureVertices, textureIndices);
			textureVertices.clear();
			textureIndices.clear();
			usedTexUnits.clear();

			glBindTextureUnit(it->second.textureUnit % max_textures_per_draw, it->first);
			usedTexUnits.push_back(it->second.textureUnit % max_textures_per_draw);
			textureVertices.insert(textureVertices.end(), it->second.vertices.begin(), it->second.vertices.end());
			ConcatIndices(textureIndices, it->second.indices);
			++textureCount;
		}
	}

	BatchRenderElements(GL_TRIANGLES, textureVertices, textureIndices);
	BatchRenderElements(GL_TRIANGLES, vertices, indices);

	if (debug)
		RenderDebug();

	allocator.UnbindVAO();
	textureProgram.Unbind();

	if (!fbo.GetRenderToScreen())
		fbo.Unbind();

	vertices.clear();
	indices.clear();
	textureVertices.clear();
	textureIndices.clear();
	debugPoints.clear();
	debugVertices.clear();
	debugIndices.clear();
}

void RenderManager::RenderDebug()
{
	for (const Entity& e : mEntities)
	{
		if (!e.GetComponent<General>().isActive) continue;

		if (e.HasComponent<Point2DCollider>() && e.GetComponent<Point2DCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale = { 0, 0 };
			t.rotation = 0;
			t.translation += e.GetComponent<Point2DCollider>().centerOffset;
			CreateDebugSquare(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<Edge2DCollider>() && e.GetComponent<Edge2DCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale *= glm::vec2(e.GetComponent<Edge2DCollider>().scaleOffset);
			t.rotation += e.GetComponent<Edge2DCollider>().rotationOffset;
			t.translation += e.GetComponent<Edge2DCollider>().p0Offset;
			CreateDebugArrow(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<RectCollider>() && e.GetComponent<RectCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale *= e.GetComponent<RectCollider>().scaleOffset;
			t.rotation = 0;
			t.translation += e.GetComponent<RectCollider>().centerOffset;
			CreateDebugSquare(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<CircleCollider>() && e.GetComponent<CircleCollider>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale = glm::vec2(std::max(t.scale.x, t.scale.y) * e.GetComponent<CircleCollider>().scaleOffset);
			t.rotation = 0;
			t.translation += e.GetComponent<CircleCollider>().centerOffset;
			CreateDebugCircle(t, e.GetComponent<Sprite>().color);
		}

		if (e.HasComponent<Physics2D>() && e.GetComponent<Physics2D>().renderFlag)
		{
			Transform t = e.GetComponent<Transform>();
			t.scale = glm::vec2(e.GetComponent<Physics2D>().speed) * vectorLengthModifier;
			t.rotation = e.GetComponent<Physics2D>().moveDirection;
			CreateDebugArrow(t, e.GetComponent<Sprite>().color);
		}

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

	BatchRenderArrays(GL_POINTS, debugPoints);
	BatchRenderElements(GL_LINES, debugVertices, debugIndices);
}

void RenderManager::BatchRenderArrays(GLenum mode, const std::vector<Vertex>& vertices)
{
	if (vertices.empty()) return;
	glNamedBufferSubData(allocator.vboid, 0, sizeof(Vertex) * vertices.size(), vertices.data());
	glDrawArrays(mode, 0, vertices.size());
}

void RenderManager::BatchRenderElements(GLenum mode, const std::vector<Vertex>& vertices, const std::vector<GLushort>& indices)
{
	if (vertices.empty()) return;
	glNamedBufferSubData(allocator.vboid, 0, sizeof(Vertex) * vertices.size(), vertices.data());
	glNamedBufferSubData(allocator.eboid, 0, indices.size() * sizeof(GLushort), indices.data());
	glDrawElements(mode, indices.size(), GL_UNSIGNED_SHORT, nullptr);
}

void RenderManager::CreateSquare(const Entity& e, std::vector<Vertex>& vertices, std::vector<GLushort>& indices)
{
	glm::mat3x3 mtx = GetTransform(e);
	glm::vec4 clr = GetColor(e);
	float layer = (e.GetComponent<Sprite>().layer * 2 - 255) / 255.f;
	float texID = e.GetComponent<Sprite>().texture;

	float texMin{};
	float texMax{1.f};

	if (e.HasComponent<SheetAnimation>())
	{
		float slice = texMax / (float)e.GetComponent<SheetAnimation>().frameCount;
		float index = (float)e.GetComponent<SheetAnimation>().currFrameIndex;

		texMin =  index * slice;
		texMax = texMin + slice;
	}

	Vertex v0, v1, v2, v3;
	v0.position = mtx * glm::vec3(-1.f, 1.f, 1.f);
	v0.position.z = layer;
	v0.color = clr;
	v0.texCoords = glm::vec2(texMin, 1.f);
	v0.texID = texID;

	v1.position = mtx * glm::vec3(-1.f, -1.f, 1.f);
	v1.position.z = layer;
	v1.color = clr;
	v1.texCoords = glm::vec2(texMin, 0.f);
	v1.texID = texID;

	v2.position = mtx * glm::vec3(1.f, 1.f, 1.f);
	v2.position.z = layer;
	v2.color = clr;
	v2.texCoords = glm::vec2(texMax, 1.f);
	v2.texID = texID;

	v3.position = mtx * glm::vec3(1.f, -1.f, 1.f);
	v3.position.z = layer;
	v3.color = clr;
	v3.texCoords = glm::vec2(texMax, 0.f);
	v3.texID = texID;

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	GLuint first = indices.empty() ? 0 : indices.back() + 1;
	indices.push_back(first);
	indices.push_back(first + 1);
	indices.push_back(first + 2);
	indices.push_back(first + 1);
	indices.push_back(first + 2);
	indices.push_back(first + 3);
}

void RenderManager::CreateCircle(const Entity& e)
{
	glm::mat3x3 mtx = GetTransform(e);
	glm::vec4 clr = GetColor(e);
	float layer = (e.GetComponent<Sprite>().layer * 2 - 255.f) / 255.f;

	float theta = 2.f / circle_slices * 3.14159265f;
	Vertex v0;
	v0.position = mtx * glm::vec3(0.f, 0.f, 1.f);
	v0.position.z = layer;
	v0.color = clr;
	v0.texID = 0.f;
	vertices.push_back(v0);

	for (int i = 1; i < circle_slices + 2; ++i)
	{
		Vertex v;
		v.position = mtx * glm::vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f);
		v.position.z = layer;
		v.color = clr;
		v.texID = 0.f;
		vertices.push_back(v);
	}

	GLuint pivot = indices.empty() ? 0 : indices.back() + 1;

	for (int i = 0; i < circle_slices; ++i)
	{
		indices.push_back(pivot);
		indices.push_back(pivot + 1 + i);
		indices.push_back(pivot + 2 + i);
	}
}

void RenderManager::CreateDebugPoint(const Entity& e)
{
	CreateDebugPoint(e.GetComponent<Transform>(), e.GetComponent<Sprite>().color);
}

void RenderManager::CreateDebugPoint(const Transform& t, const Color& c)
{
	glm::vec4 clr = GetColor(c.r, c.g, c.b, c.a);
	glm::mat3x3 mtx = GetTransform({ 0, 0 }, 0, t.translation);

	Vertex v0;
	v0.color = clr;
	v0.position = mtx * glm::vec3(0, 0, 1.f);
	v0.texID = 0.f;
	v0.position.z = 1;

	debugPoints.push_back(v0);
}

void RenderManager::CreateDebugLine(const Entity& e)
{
	CreateDebugLine(e.GetComponent<Transform>(), e.GetComponent<Sprite>().color);
}

void RenderManager::CreateDebugLine(const Transform& t, const Color& c)
{
	glm::vec4 clr = GetColor(c.r, c.g, c.b, c.a);
	glm::mat3x3 mtx = GetTransform(t.scale, t.rotation, t.translation);

	Vertex v0, v1;
	v0.color = clr;
	v0.position = mtx * glm::vec3(0.f, 0.f, 1.f);
	v0.position.z = 1;
	v0.texID = 0.f;

	v1.color = clr;
	v1.position = mtx * glm::vec3(1.f, 0.f, 1.f);
	v1.position.z = 1;
	v1.texID = 0.f;

	debugVertices.push_back(v0);
	debugVertices.push_back(v1);

	GLuint first = debugIndices.empty() ? 0 : debugIndices.back() + 1;
	debugIndices.push_back(first);
	debugIndices.push_back(first + 1);
}

void RenderManager::CreateDebugSquare(const Entity& e)
{
	CreateDebugSquare(e.GetComponent<Transform>(), e.GetComponent<Sprite>().color);
}

void RenderManager::CreateDebugSquare(const Transform& t, const Color& c)
{
	glm::mat3x3 mtx = GetTransform(t.scale, t.rotation, t.translation);
	glm::vec4 clr = GetColor(c.r, c.g, c.b, c.a);
	Vertex v0, v1, v2, v3;
	v0.position = mtx * glm::vec3(-1.f, 1.f, 1.f);
	v0.position.z = 1;
	v0.color = clr;
	v0.texID = 0.f;

	v1.position = mtx * glm::vec3(-1.f, -1.f, 1.f);
	v1.position.z = 1;
	v1.color = clr;
	v1.texID = 0.f;

	v2.position = mtx * glm::vec3(1.f, 1.f, 1.f);
	v2.position.z = 1;
	v2.color = clr;
	v2.texID = 0.f;

	v3.position = mtx * glm::vec3(1.f, -1.f, 1.f);
	v3.position.z = 1;
	v3.color = clr;
	v3.texID = 0.f;

	debugVertices.push_back(v0);
	debugVertices.push_back(v1);
	debugVertices.push_back(v3);
	debugVertices.push_back(v2);

	GLuint first = debugIndices.empty() ? 0 : debugIndices.back() + 1;
	debugIndices.push_back(first);
	debugIndices.push_back(first + 1);
	debugIndices.push_back(first + 1);
	debugIndices.push_back(first + 2);
	debugIndices.push_back(first + 2);
	debugIndices.push_back(first + 3);
	debugIndices.push_back(first);
	debugIndices.push_back(first + 3);
}

void RenderManager::CreateDebugCircle(const Entity& e)
{
	CreateDebugCircle(e.GetComponent<Transform>(), e.GetComponent<Sprite>().color);
}

void RenderManager::CreateDebugCircle(const Transform& t, const Color& c)
{
	glm::mat3x3 mtx = GetTransform(t.scale, t.rotation, t.translation);
	glm::vec4 clr = GetColor(c.r, c.g, c.b, c.a);

	float theta = 2.f / circle_slices * 3.14159265f;

	for (int i = 1; i < circle_slices + 2; ++i)
	{
		Vertex v;
		v.position = mtx * glm::vec3(cosf((i - 1) * theta), sinf((i - 1) * theta), 1.f);
		v.position.z = 1;
		v.color = clr;
		v.texID = 0.f;
		debugVertices.push_back(v);
	}

	GLuint first = debugIndices.empty() ? 0 : debugIndices.back() + 1;

	for (int i = 0; i < circle_slices; ++i)
	{
		debugIndices.push_back(first + i);
		debugIndices.push_back(first + i + 1);
	}
}

void RenderManager::CreateDebugArrow(const Entity& e)
{
	CreateDebugLine(e);
	debugPoints.push_back(debugVertices.back());
}

void RenderManager::CreateDebugArrow(const Transform& t, const Color& c)
{
	CreateDebugLine(t, c);
	debugPoints.push_back(debugVertices.back());
}

void RenderManager::SetDebug(bool set)
{
	debug = set;
}

void RenderManager::SetVectorLengthModifier(float modifier)
{
	vectorLengthModifier = modifier;
}

glm::mat3x3 RenderManager::GetTransform(const Entity& e)
{
	return GetTransform(e.GetComponent<Transform>().scale, e.GetComponent<Transform>().rotation,
		e.GetComponent<Transform>().translation);
}

glm::mat3x3 RenderManager::GetTransform(const glm::vec2& scale, float rotate, const glm::vec2& translate)
{
	float cosRot = cosf(rotate);
	float sinRot = sinf(rotate);

	glm::mat3x3 temp =
	{ 
		glm::vec3(scale.x * cosRot, scale.x * sinRot, 0.f),
		glm::vec3(-scale.y * sinRot, scale.y * cosRot, 0.f),
		glm::vec3(translate.x, translate.y, 1.f) 
	};

	temp[0][0] /= (float)Application::getWindowWidth();
	temp[0][1] /= (float)Application::getWindowHeight();
	temp[1][0] /= (float)Application::getWindowWidth();
	temp[1][1] /= (float)Application::getWindowHeight();
	temp[2][0] /= (float)Application::getWindowWidth() / 2.f;
	temp[2][1] /= (float)Application::getWindowHeight() / 2.f;

	return temp;
}

glm::vec4 RenderManager::GetColor(const Entity& e)
{
	return GetColor(e.GetComponent<Sprite>().color.r, e.GetComponent<Sprite>().color.g,
		e.GetComponent<Sprite>().color.b, e.GetComponent<Sprite>().color.a);
}

glm::vec4 RenderManager::GetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	return { r / 255.f, g / 255.f, b / 255.f, a / 255.f };
}

void RenderManager::InitializeShaders()
{
	textureProgram.CompileLinkShaders();

	if (!textureProgram.Validate())
	{
		std::cout << "Unable to validate shader programs\n";
		std::exit(EXIT_FAILURE);
	}
}


void RenderManager::ConcatIndices(std::vector<GLushort>& first, std::vector<GLushort>& second)
{
	if (first.empty())
	{
		for (GLushort& idx : second)
			first.push_back(idx);
		return;
	}
	GLushort back = first.back();
	for (GLushort idx : second)
	{
		idx += back + 1;
		first.push_back(idx);
	}
}
