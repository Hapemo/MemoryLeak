/*!*****************************************************************************
\file RenderManager.h
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for the class RenderManager, which 
operates on Entities with Sprite and Transform Components.
*******************************************************************************/
#pragma once
#include "Graphics/GLAllocator.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ECS_systems.h>
#include "ECS_items.h"
#include "ECS_components.h"
#include "Graphics/GLShader.h"
#include "PerformanceVisualiser.h"
#include "Graphics/FBO.h"
#include "FontManager.h"
#include "Camera.h"

enum class RENDER_STATE { WORLD, GAME };

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

/*!*****************************************************************************
\brief
RenderManager Class that handles rendering of Entities with Sprite and Transform
Component.
*******************************************************************************/
class RenderManager : public System
{
public:
	/*!*****************************************************************************
	\brief
	Default Constructor for RenderManager class.
	*******************************************************************************/
	RenderManager();

	/*!*****************************************************************************
	\brief
	Initializes the RenderManager class.

	\param int* _windowWidth
	Pixel width of the window.

	\param int* _windowHeight
	Pixel height of the window.
	*******************************************************************************/
	void Init(int* _windowWidth, int* _windowHeight);

	/*!*****************************************************************************
	\brief
	Render Entities with Sprite and Transform Component.
	*******************************************************************************/
	void Render();

	/*!*****************************************************************************
	\brief
	Clears the background. Mainly used for switching states.
	*******************************************************************************/
	void Clear();

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
	Returns the color attachment to the frame buffer.

	\return
	Returns the color attachment to the frame buffer.
	*******************************************************************************/
	GLuint GetWorldFBO() const { return mWorldFBO.GetColorAttachment(); }

	/*!*****************************************************************************
	\brief
	Returns the color attachment to the frame buffer.

	\return
	Returns the color attachment to the frame buffer.
	*******************************************************************************/
	GLuint GetGameFBO() const { return mGameFBO.GetColorAttachment(); }

	/*!*****************************************************************************
	\brief
	Rendering will be done to the screen instead of the FBO.
	*******************************************************************************/
	void RenderToScreen() { mRenderGameToScreen = true; }

	/*!*****************************************************************************
	\brief
	Rendering will be done to the FBO instead of the screen.
	*******************************************************************************/
	void RenderToFrameBuffer() { mRenderGameToScreen = false; }

	/*!*****************************************************************************
	\brief
	Function that returns the transform of an Entity for use with ImGuizmo

	\param const Entity& _e
	Entity to get the Transformation matrix of.

	\return std::vector<float>
	Transformation matrix of the Entity.
	*******************************************************************************/
	std::vector<float> GetImGuizmoMat4(const Entity& _e);

	Camera& GetWorldCamera() { return mWorldCam; }
	Camera& GetGameCamera() { return mGameCam; }

private:
	RENDER_STATE mCurrRenderPass;
	Camera mWorldCam, mGameCam;
	FontManager mFontManager;
	bool mDebug, mRenderGameToScreen;
	float mVectorLengthModifier;
	FBO mWorldFBO, mGameFBO;
	int* mWindowWidth;
	int* mWindowHeight;
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
	Helper function for returning the color of the Sprite Component in OpenGL.

	\param const Entity& _e
	The entity containing Transform and Sprite component.

	\return
	Returns the color of the Sprite.
	*******************************************************************************/
	glm::vec4 GetColor(const Entity& _e);

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
	glm::vec4 GetColor(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a);

	/*!*****************************************************************************
	\brief
	Helper function for returning the Transformation matrix of a Component.

	\param const Entity& _e
	The entity containing Transform and Sprite component.

	\return
	The Transformation matrix.
	*******************************************************************************/
	Math::Mat3 GetTransform(const Entity& _e);

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
	Math::Mat3 GetTransform(const Math::Vec2& _scale, float _rotate, const Math::Vec2& _translate);

	/*!*****************************************************************************
	\brief
	Initializes the Shader program.
	*******************************************************************************/
	void InitializeShaders();

	/*!*****************************************************************************
	\brief
	Helper function for concatenating the vector of indices.

	\param std::vector<GLushort>& _first
	The vector for indices to be pushed into.

	\param std::vector<GLushort>& _second
	The vector for indices to be taken from.
	*******************************************************************************/
	void ConcatIndices(std::vector<GLushort>& _first, std::vector<GLushort>& _second);
};



