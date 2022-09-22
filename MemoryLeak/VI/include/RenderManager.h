#pragma once
#include "GLAllocator.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include "GLShader.h"
#include "PerformanceVisualiser.h"
#include "FBO.h"

struct TextureInfo
{
	int textureUnit;
	std::vector<Vertex> vertices;
	std::vector<GLushort> indices;
};

class RenderManager : public System
{
public:
	RenderManager();
	void Init(int*, int*);
	void Render();
	void SetDebug(bool);
	void SetVectorLengthModifier(float);
	GLuint GetFBO() const { return fbo.GetColorAttachment(); }
	void RenderToScreen() { fbo.SetRenderToScreen(true); }
	void RenderToFrameBuffer() { fbo.SetRenderToScreen(false); }

private:
	bool debug;
	float vectorLengthModifier;
	FBO fbo;
	//GLShader defaultProgram;
	int* mWindowWidth;
	int* mWindowHeight;
	GLShader textureProgram;
	GLAllocator allocator;
	std::vector<Vertex> vertices;
	std::vector<GLushort> indices;
	std::vector<Vertex> textureVertices;
	std::vector<GLushort> textureIndices;
	std::vector<Vertex> debugPoints;
	std::vector<Vertex> debugVertices;
	std::vector<GLushort> debugIndices;

	void RenderDebug();
	void BatchRenderArrays(GLenum mode, const std::vector<Vertex>& vertices);
	void BatchRenderElements(GLenum mode, const std::vector<Vertex>& vertices, const std::vector<GLushort>& indices);

	void CreateSquare(const Entity& e, std::vector<Vertex>& vertices, std::vector<GLushort>& indices);
	void CreateCircle(const Entity& e);
	void CreateDebugPoint(const Entity& e);
	void CreateDebugPoint(const Transform& t, const Color& c);
	void CreateDebugLine(const Entity& e);
	void CreateDebugLine(const Transform& t, const Color& c);
	void CreateDebugSquare(const Entity& e);
	void CreateDebugSquare(const Transform& t, const Color& c);
	void CreateDebugCircle(const Entity& e);
	void CreateDebugCircle(const Transform& t, const Color& c);
	void CreateDebugArrow(const Entity& e);
	void CreateDebugArrow(const Transform& t, const Color& c);
	
	glm::vec4 GetColor(const Entity& e);
	glm::vec4 GetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	glm::mat3x3 GetTransform(const Entity& e);
	glm::mat3x3 GetTransform(const glm::vec2& scale, float rotate, const glm::vec2& translate);

	void InitializeShaders();
	void ConcatIndices(std::vector<GLushort>& first, std::vector<GLushort>& second);
};



