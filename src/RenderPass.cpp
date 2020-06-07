#include "RenderPass.h"
#include "Renderer.h"

#include "LightPass.h"
#include "GUI.h"

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

	GLuint finalTexture = 0;
	switch (GUI::getInstance()->getRenderMode())
	{
		case RenderMode::FINAL:
		{
			Renderer::getInstance()->getBuffer("LightBuffer")->BindFrameBuffer();
			finalTexture = Renderer::getInstance()->getBuffer("LightBuffer")->getTexturesList()[LightPass::TexturesOut::LightingOut];
			break;
		}
		case RenderMode::POSITION:
		{
			Renderer::getInstance()->getBuffer("GeometryBuffer")->BindFrameBuffer();
			finalTexture = Renderer::getInstance()->getBuffer("GeometryBuffer")->getTexturesList()[GeometryPass::TexturesOut::Position];
			break;
		}
		case RenderMode::NORMAL:
		{
			Renderer::getInstance()->getBuffer("GeometryBuffer")->BindFrameBuffer();
			finalTexture = Renderer::getInstance()->getBuffer("GeometryBuffer")->getTexturesList()[GeometryPass::TexturesOut::Normal];
			break;
		}
		case RenderMode::DIFFUSE:
		{
			Renderer::getInstance()->getBuffer("GeometryBuffer")->BindFrameBuffer();
			finalTexture = Renderer::getInstance()->getBuffer("GeometryBuffer")->getTexturesList()[GeometryPass::TexturesOut::DiffuseColor];
			break;
		}
		case RenderMode::SPECULAR:
		{
			Renderer::getInstance()->getBuffer("GeometryBuffer")->BindFrameBuffer();
			finalTexture = Renderer::getInstance()->getBuffer("GeometryBuffer")->getTexturesList()[GeometryPass::TexturesOut::SpecularColor];
			break;
		}
		case RenderMode::AMBIENT:
		{
			Renderer::getInstance()->getBuffer("GeometryBuffer")->BindFrameBuffer();
			finalTexture = Renderer::getInstance()->getBuffer("GeometryBuffer")->getTexturesList()[GeometryPass::TexturesOut::AmbientColor];
			break;
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, finalTexture);

	program_->setUniform("TextureToRender", 2);

	//To output IRenderable
	Renderer::getInstance()->getOutputRenderable()->Render();
}
