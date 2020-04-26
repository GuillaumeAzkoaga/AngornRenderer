#include "GeometryPass.h"
#include "Renderer.h"
#include "RenderView.h"
#include "RenderingUtils.h"
#include "Camera.h"
#include "Light.h"

GeometryPass::GeometryPass()
{	
	gBuffer_ = new GBuffer();
	Renderer::getInstance()->RegisterBuffer("GeometryBuffer", gBuffer_);

	gBuffer_->Initialize(RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight(), TexturesOut::NUM_TEXTURES, true);

	Shader* vertShader = Renderer::getInstance()->getShader(GL_VERTEX_SHADER, GEOMETRY_VERTEX_FILE);
	Shader* fragShader = Renderer::getInstance()->getShader(GL_FRAGMENT_SHADER, GEOMETRY_FRAGMENT_FILE);

	Shader* TessControlShader = Renderer::getInstance()->getShader(GL_TESS_CONTROL_SHADER, TESS_CONTROL_FILE);
	Shader* TessEvalShader = Renderer::getInstance()->getShader(GL_TESS_EVALUATION_SHADER, TESS_EVAL_FILE);

	program_ = new ShaderProgram();
	program_->AttachShader(vertShader);
	program_->AttachShader(TessControlShader);
	program_->AttachShader(TessEvalShader);
	program_->AttachShader(fragShader);

	program_->LinkProgram();
}


void GeometryPass::Apply()
{
	program_->UseProgram();
	gBuffer_->BindFrameBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_->setUniform("projection", Camera::getInstance()->getProjectionMtx());
	program_->setUniform("view", Camera::getInstance()->getViewMtx());
	program_->setUniform("camera_pos", Camera::getInstance()->getPosition());

	std::vector<IRenderable*> renderables = Renderer::getInstance()->getRenderables();
	for (IRenderable* renderable : renderables)
	{
		if (renderable == nullptr)
			continue;

		//Mesh uniforms
		program_->setUniform("model", renderable->getModelMatrix());
			
		//Tesselation uniforms
		program_->setUniform("uTessAlpha",0.7f);
		program_->setUniform("uTessLevelsOuter", 10.0f);
		program_->setUniform("uTessLevelsInner", 10.0f);
		program_->setUniform("slope", -0.00001f);
		program_->setUniform("m", 0.4f);
		program_->setUniform("useAdaptive", 0);
		
		//Texture uniforms
		const Texture* texture = renderable->getTexture();
		if (texture)
		{
			program_->setUniform("hasTextures", 1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getDiffuseTexture());
			program_->setUniform("textureDiffuse", 0);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture->getSpecularTexture());
			program_->setUniform("textureSpecular", 1);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture->getAmbientTexture());
			program_->setUniform("textureAmbient", 2);
		}
		else
		{
			program_->setUniform("hasTextures", 0);

			//Material uniforms
			const Material* material = renderable->getMaterial();			
			program_->setUniform("materialDiffuse", material->getDiffuseColor());
			program_->setUniform("materialSpecular", material->getSpecularColor());
			program_->setUniform("materialAmbient", material->getAmbientColor());
		}	

		glPatchParameteri(GL_PATCH_VERTICES, 3);
		renderable->Render(GL_PATCHES, false);
	}

	glEnable(GL_CULL_FACE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glCheckError();
}
