#pragma once
#include <pch.h>
#include "Graphics/GLAllocator.h"
#include "Graphics/GLShader.h"
#include "Graphics/FBO.h"
#include "FontManager.h"
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"

/*!*****************************************************************************
\brief
Struct that encapsulates what is needed when rendering a texture in OpenGL.
*******************************************************************************/
struct TextureInfo
{
	int mTextureUnit;
	std::vector<Vertex> mVertices;
	std::vector<GLushort> mIndices;
};

class Renderer
{
public:
	Renderer();
private:
	FBO mfbo;
	bool mDebug;
	float mVectorLengthModifier;
	FontManager fontManager;
	GLShader mDefaultProgram;
	GLShader mTextureProgram;
	GLAllocator mAllocator;
	std::vector<Vertex> mVertices;
	std::vector<GLushort> mIndices;
	std::vector<Vertex> mTextureVertices;
	std::vector<GLushort> mTextureIndices;
	std::vector<Vertex> mDebugPoints;
	std::vector<Vertex> mDebugVertices;
	std::vector<GLushort> mDebugIndices;

	/*!*****************************************************************************
	\brief
	Renders debug drawings.
	*******************************************************************************/
	void RenderDebug();

	/*!*****************************************************************************
	\brief
	Binds a Texture Unit to an image.

	\param GLuint& _texID
	Texture ID of the texture to be rendered.

	\param TextureInfo& _texInfo
	Struct containing texture unit ID, vertices and indices.

	\param std::vector<int>& _texUnits
	Current texture units that are in use.
	*******************************************************************************/
	void BindTextureUnit(const GLuint& _texID, TextureInfo& _texInfo, std::vector<int>& _texUnits);

	/*!*****************************************************************************
	\brief
	Batch Rendering of vertices.

	\param GLenum _mode
	Mode of rendering (GL_LINES, GL_TRIANGLES, etc..)

	\param const std::vector<Vertex>& _vertices
	Vertices array to be rendered.
	*******************************************************************************/
	void BatchRenderArrays(GLenum _mode, const std::vector<Vertex>& _vertices);

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
	void BatchRenderElements(GLenum _mode, const std::vector<Vertex>& _vertices, const std::vector<GLushort>& _indices);

	/*!*****************************************************************************
	\brief
	Batch Rendering of vertices with Element Buffer Object.

	\param const std::vector<Vertex>& _vertices
	Vertices array to be rendered.

	\param const std::vector<GLushort>& _indices
	Indices of the vertex array.

	\param std::vector<int>& _texUnits
	Current texture units that are in use.
	*******************************************************************************/
	void BatchRenderTextures(int& _texCount, std::vector<int>& _texUnits);

	/*!*****************************************************************************
	\brief
	Sets the debug mode of rendering.

	\param bool
	Renders debug drawings if debug mode is set to true.
	*******************************************************************************/
	void SetDebug(bool);

	/*!*****************************************************************************
	\brief
	Sets the modifier for the length of the debug vector.

	\param float
	Modifier for the length of the vector.
	*******************************************************************************/
	void SetVectorLengthModifier(float);

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
	void CreateSquare(const Entity& _e, std::vector<Vertex>& _vertices, std::vector<GLushort>& _indices);

	/*!*****************************************************************************
	\brief
	Creates a circle based on Transform and Sprite Component.

	\param const Entity& _e
	The entity containing Transform and Sprite component.
	*******************************************************************************/
	void CreateCircle(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Creates a debug point based on Transform and Sprite Component, or Physics point
	collider.

	\param const Entity& _e
	The entity containing Transform and Sprite component.
	*******************************************************************************/
	void CreateDebugPoint(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Creates a debug point based on Transform and Sprite Component, or Physics point
	collider.

	\param const Transform& _t
	The transform component.

	\param const Color& _c
	The color component.
	*******************************************************************************/
	void CreateDebugPoint(const Transform& _t, const Color& _c);

	/*!*****************************************************************************
	\brief
	Creates a debug line based on Transform and Sprite Component, or Physics Edge
	Collider.

	\param const Entity& _e
	The entity containing Transform and Sprite component.
	*******************************************************************************/
	void CreateDebugLine(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Creates a debug line based on Transform and Sprite Component, or Physics Edge
	Collider.

	\param const Transform& _t
	The transform component.

	\param const Color& _c
	The color component.
	*******************************************************************************/
	void CreateDebugLine(const Transform& _t, const Color& _c);

	/*!*****************************************************************************
	\brief
	Creates a debug Square based on Transform and Sprite Component, or Physics Rect
	Collider.

	\param const Entity& _e
	The entity containing Transform and Sprite component.
	*******************************************************************************/
	void CreateDebugSquare(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Creates a debug Square based on Transform and Sprite Component, or Physics Rect
	Collider.

	\param const Transform& _t
	The transform component.

	\param const Color& _c
	The color component.
	*******************************************************************************/
	void CreateDebugSquare(const Transform& _t, const Color& _c);

	/*!*****************************************************************************
	\brief
	Creates a debug circle based on Transform and Sprite Component, or Physics Circle
	Collider.

	\param const Entity& _e
	The entity containing Transform and Sprite component.
	*******************************************************************************/
	void CreateDebugCircle(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Creates a debug circle based on Transform and Sprite Component, or Physics Circle
	Collider.

	\param const Transform& _t
	The transform component.

	\param const Color& _c
	The color component.
	*******************************************************************************/
	void CreateDebugCircle(const Transform& _t, const Color& _c);

	/*!*****************************************************************************
	\brief
	Creates a debug arrow based on Transform and Sprite Component, or Physics2D
	component.

	\param const Entity& _e
	The entity containing Transform and Sprite component.
	*******************************************************************************/
	void CreateDebugArrow(const Entity& _e);

	/*!*****************************************************************************
	\brief
	Creates a debug arrow based on Transform and Sprite Component, or Physics2D
	component.

	\param const Transform& _t
	The transform component.

	\param const Color& _c
	The color component.
	*******************************************************************************/
	void CreateDebugArrow(const Transform& _t, const Color& _c);

	/*!*****************************************************************************
	\brief
	Initializes the Shader program.
	*******************************************************************************/
	void InitializeShaders();
};