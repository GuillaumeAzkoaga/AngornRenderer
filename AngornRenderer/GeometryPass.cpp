#include "GeometryPass.h"
#include "Renderer.h"
#include "RenderView.h"
#include "RenderingUtils.h"
#include "Camera.h"

GeometryPass::GeometryPass()
{
	
	gBuffer_ = new GBuffer();
	Renderer::getInstance()->RegisterBuffer("GeometryBuffer", gBuffer_);

	gBuffer_->Initialize(RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight(), TexturesOut::NUM_TEXTURES, true);

	Shader* vertShader = Renderer::getInstance()->getShader(GL_VERTEX_SHADER, GEOMETRY_VERTEX_FILE);
	Shader* fragShader = Renderer::getInstance()->getShader(GL_FRAGMENT_SHADER, GEOMETRY_FRAGMENT_FILE);

	program_ = new ShaderProgram();
	program_->AttachShader(vertShader);
	program_->AttachShader(fragShader);
	program_->LinkProgram();
}


void GeometryPass::Apply()
{
	program_->UseProgram();
	gBuffer_->BindFrameBuffer();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<IRenderable*> renderables = Renderer::getInstance()->getRenderables();
	for (IRenderable* renderable : renderables)
	{
		if (renderable == nullptr)
			continue;

		//Matrices uniforms
		renderable->ComputeMatrices();
		program_->setUniform("ModelViewMatrix", renderable->getModelmtx());		

		//Material uniforms
		program_->setUniform("material.diffuse", renderable->getMaterial()->getDiffuseColor());
		program_->setUniform("material.specular", renderable->getMaterial()->getSpecularColor());
		program_->setUniform("material.ambient", renderable->getMaterial()->getAmbientColor());
		
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		renderable->Render(GL_PATCHES, false);
	}

	glEnable(GL_CULL_FACE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glCheckError();
}
