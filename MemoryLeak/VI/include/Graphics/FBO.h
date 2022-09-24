/*!*****************************************************************************
\file FBO.h
\author Kew Yu Jun
\par DP email: k.yujun\@digipen.edu
\par Group: Memory Leak Studios
\date 20-09-2022
\brief
This file contains function declarations for a Frame Buffer Object (FBO) class 
to operate on OpenGL's Frame Buffer Object.
*******************************************************************************/
#pragma once
#include "pch.h"
#include "Graphics/GLAllocator.h"

/*!*****************************************************************************
\brief
Struct that encapsulates specifications in a user defined FBO.
*******************************************************************************/
struct FBOSpec 
{
	/*!*****************************************************************************
	\brief
	Default constructor for FBOSpec class.
	*******************************************************************************/
	FBOSpec();
	int mWidth;
	int mHeight;
	int mSamples;
	bool mRenderToScreen;
};

/*!*****************************************************************************
\brief
Struct that emulates and simplifies OpenGL's FBO.
*******************************************************************************/
class FBO
{
public:
	/*!*****************************************************************************
	\brief
	Default constructor for FBOSpec class.
	*******************************************************************************/
	FBO() : mfboid(), mColorAttachment(), mDepthAttachment(), mSpecs() {};
	/*!*****************************************************************************
	\brief
	Destructor for FBOSpec class.
	*******************************************************************************/
	~FBO();
	/*!*****************************************************************************
	\brief
	Initializes the FBO Class.

	\param int _width
	Pixel width of the FBO

	\param int _height
	Pixel height of the FBO
	*******************************************************************************/
	void Init(int _width, int _height);
	/*!*****************************************************************************
	\brief
	Binds the FBO to the OpenGL context.
	*******************************************************************************/
	void Bind();
	/*!*****************************************************************************
	\brief
	Unbinds the FBO from the OpenGL context.
	*******************************************************************************/
	void Unbind();
	/*!*****************************************************************************
	\brief
	A flag to set for rendering to screen or to the frame buffer.

	\param bool scrn
	True for rendering to screen, false for rendering to the frame buffer.
	*******************************************************************************/
	void SetRenderToScreen(bool _scrn) { mSpecs.mRenderToScreen = _scrn; }
	/*!*****************************************************************************
	\brief
	Returns the state of the RenderToScreen flag.

	\return
	Returns the state of the RenderToScreen flag.
	*******************************************************************************/
	bool GetRenderToScreen() { return mSpecs.mRenderToScreen; }
	/*!*****************************************************************************
	\brief
	Returns the ID of the FBO.

	\return
	Returns the ID of the FBO.
	*******************************************************************************/
	GLuint GetID() const { return mfboid; }
	/*!*****************************************************************************
	\brief
	Returns the ID of the color attachment.

	\return
	Returns the ID of the color attachment.
	*******************************************************************************/
	GLuint GetColorAttachment() const { return mColorAttachment; }
	/*!*****************************************************************************
	\brief
	Returns the ID of the depth attachment.

	\return
	Returns the ID of the depth attachment.
	*******************************************************************************/
	GLuint GetDepthAttachment() const { return mDepthAttachment; }
	/*!*****************************************************************************
	\brief
	Returns the pixel width of the FBO.

	\return
	Returns the pixel width of the FBO.
	*******************************************************************************/
	int GetFBOWidth() const { return mSpecs.mWidth; }
	/*!*****************************************************************************
	\brief
	Returns the pixel height of the FBO.

	\return
	Returns the pixel height of the FBO.
	*******************************************************************************/
	int GetFBOHeight() const { return mSpecs.mHeight; }

private:
	GLuint mfboid;
	GLuint mColorAttachment;
	GLuint mDepthAttachment;
	FBOSpec mSpecs;
};

