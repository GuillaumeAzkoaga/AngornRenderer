#include "GBuffer.h"
#include "RenderView.h"

void GBuffer::Initialize(const unsigned int windowWidth, const unsigned int windowHeight, const unsigned textureAmount, const bool useDepth)
{
	isUsingDepth_ = useDepth;

	//Create the FBO
	glGenFramebuffers(1, &frameBufferOject_);
	BindFrameBuffer();

	//Create the GBuffer textures
	textureList_.resize(textureAmount);
	glGenTextures(textureAmount, textureList_.data());
	if(isUsingDepth_)
		glGenTextures(1, &depthTexture_);

	for (unsigned int i = 0; i < textureAmount; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textureList_[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, RenderView::getInstance()->getWidth() , RenderView::getInstance()->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureList_[i], 0);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	if (isUsingDepth_)
	{
		glBindTexture(GL_TEXTURE_2D, depthTexture_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture_, 0);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}


	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0,
								GL_COLOR_ATTACHMENT1,
								GL_COLOR_ATTACHMENT2,
								GL_COLOR_ATTACHMENT3,
								GL_COLOR_ATTACHMENT4 };

	glDrawBuffers(textureAmount, DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		MessageBox(NULL, std::string("FrameBuffer not complete. Status: " + Status).c_str(), "GBuffer Initialization error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
		return;
	}

	// restore default FBO
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::BindFrameBuffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferOject_);
}

