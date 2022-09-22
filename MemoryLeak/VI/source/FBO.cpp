#include "FBO.h"

FBOSpec::FBOSpec()
{
	width = Application::getWindowWidth();
	height = Application::getWindowHeight();
	samples = 1;
	renderToScreen = true;
}

FBO::FBO(const FBOSpec& specs) : specs(specs)
{
	glCreateFramebuffers(1, &fboid);
	Bind();

	glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specs.width, specs.height, 
		0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment); 
	glBindTexture(GL_TEXTURE_2D, depthAttachment);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, specs.width, specs.height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment, 0); 

	if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
	{
		std::cout << "framebuffer spoil lol" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Unbind();
}

FBO::~FBO()
{
	glDeleteFramebuffers(1, &fboid);
}

void FBO::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboid);
}

void FBO::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}