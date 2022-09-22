#pragma once
#include "pch.h"
#include "Graphics/GLAllocator.h"
#include <glm/glm.hpp>

struct FBOSpec 
{
	FBOSpec();
	int width;
	int height;
	int samples;
	bool renderToScreen;
};

class FBO
{
public:
	FBO() : fboid(), colorAttachment(), depthAttachment(), specs() {};
	~FBO();
	void Init(int, int);
	void Bind();
	void Unbind();
	void SetRenderToScreen(bool scrn) { specs.renderToScreen = scrn; }
	bool GetRenderToScreen() { return specs.renderToScreen; }
	GLuint GetID() const { return fboid; }
	GLuint GetColorAttachment() const { return colorAttachment; }
	GLuint GetDepthAttachment() const { return depthAttachment; }
	int GetFBOWidth() const { return specs.width; }
	int GetFBOHeight() const { return specs.height; }

private:
	GLuint fboid;
	GLuint colorAttachment;
	GLuint depthAttachment;
	FBOSpec specs;
};

