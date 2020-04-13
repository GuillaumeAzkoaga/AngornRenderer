#include "RenderPass.h"
#include "Renderer.h"

#include "LightPass.h"

RenderPass::RenderPass()
{
	Shader* vertShader = Renderer::getInstance()->getShader(GL_VERTEX_SHADER, RENDER_VERTEX_FILE);
	Shader* fragShader = Renderer::getInstance()->getShader(GL_FRAGMENT_SHADER, RENDER_FRAGMENT_FILE);

	program_ = new ShaderProgram();
	program_->AttachShader(vertShader);
	program_->AttachShader(fragShader);
	program_->LinkProgram();
}

void RenderPass::Apply()
{
	program_->UseProgram();

	//TODO: Allow to switch between different final buffers (with ImGui?)
	Renderer::getInstance()->getBuffer("LightBuffer")->BindFrameBuffer();
	GLuint FinalTexture = Renderer::getInstance()->getBuffer("LightBuffer")->getTexturesList()[LightPass::TexturesOut::LightingOut];

	Renderer::getInstance()->getBuffer("GeometryBuffer")->BindFrameBuffer();
	GLuint NormalTexture = Renderer::getInstance()->getBuffer("GeometryBuffer")->getTexturesList()[GeometryPass::TexturesOut::Normal];


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, NormalTexture);

	program_->setUniform("TextureToRender", 2);

	//To output IRenderable
	Renderer::getInstance()->getOutputRenderable()->Render();
}
