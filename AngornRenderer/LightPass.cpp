#include "LightPass.h"
#include "Renderer.h"
#include "RenderView.h"
#include "RenderingUtils.h"
#include "Camera.h"
#include "Light.h"
#include "Application.h"

LightPass::LightPass()
{
	lightBuffer_ = new GBuffer();
	Renderer::getInstance()->RegisterBuffer("LightBuffer", lightBuffer_);
	lightBuffer_->Initialize(RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight(), TexturesOut::NUM_TEXTURES, false);

	Shader* vertShader = Renderer::getInstance()->getShader(GL_VERTEX_SHADER, MULTILIGHTING_VERTEX_FILE);
	Shader* fragShader = Renderer::getInstance()->getShader(GL_FRAGMENT_SHADER, MULTILIGHTING_FRAGMENT_FILE);

	program_ = new ShaderProgram();
	program_->AttachShader(vertShader);
	program_->AttachShader(fragShader);
	program_->LinkProgram();
}

void LightPass::Apply()
{
	program_->UseProgram();
	lightBuffer_->BindFrameBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Get the GeometryBuffer and bind the Geometry Pass textures
	GBuffer* geometryBuffer = Renderer::getInstance()->getBuffer("GeometryBuffer");

	//Position Texture
	glActiveTexture(GL_TEXTURE0 + GeometryPass::TexturesOut::Position);
	glBindTexture(GL_TEXTURE_2D, geometryBuffer->getTexturesList()[GeometryPass::Position]);
	program_->setUniform("PositionTexture", GeometryPass::TexturesOut::Position);
	//Normal Texture
	glActiveTexture(GL_TEXTURE0 + GeometryPass::TexturesOut::Normal);
	glBindTexture(GL_TEXTURE_2D, geometryBuffer->getTexturesList()[GeometryPass::Normal]);
	program_->setUniform("NormalTexture", GeometryPass::TexturesOut::Normal);
	//Diffuse Color Texture
	glActiveTexture(GL_TEXTURE0 + GeometryPass::TexturesOut::DiffuseColor);
	glBindTexture(GL_TEXTURE_2D, geometryBuffer->getTexturesList()[GeometryPass::DiffuseColor]);
	program_->setUniform("DiffuseColorTexture", GeometryPass::TexturesOut::DiffuseColor);
	//Specular Color Texture
	glActiveTexture(GL_TEXTURE0 + GeometryPass::TexturesOut::SpecularColor);
	glBindTexture(GL_TEXTURE_2D, geometryBuffer->getTexturesList()[GeometryPass::SpecularColor]);
	program_->setUniform("SpecularColorTexture", GeometryPass::TexturesOut::SpecularColor);
	//Ambient Color Texture
	glActiveTexture(GL_TEXTURE0 + GeometryPass::TexturesOut::AmbientColor);
	glBindTexture(GL_TEXTURE_2D, geometryBuffer->getTexturesList()[GeometryPass::AmbientColor]);
	program_->setUniform("AmbientColorTexture", GeometryPass::TexturesOut::AmbientColor);
	
	glDisable(GL_DEPTH_TEST);
	//Get lights data
	const std::vector<Light*> lights = Application::getInstance()->getLights();
	//TODO. make this cleaner
	int index = 0;
	for (auto it(lights.cbegin()), end(lights.cend()); it != end; ++it, ++index)
	{
		Light* light = *it;
		
		char temp[32];
		sprintf_s(temp, "lights[%d].color", index);
		program_->setUniform(temp, light->getColor());
		sprintf_s(temp, "lights[%d].intensity", index);
		program_->setUniform(temp, light->getIntensity());
		sprintf_s(temp, "lights[%d].pos", index);
		program_->setUniform(temp, light->getPosition());
	}
	program_->setUniform("uLightAmount", (int)(lights.size()));

	program_->setUniform("viewPos", Camera::getInstance()->getPosition());


	//To output IRenderable
	Renderer::getInstance()->getOutputRenderable()->Render();

	glEnable(GL_DEPTH_TEST);
}
