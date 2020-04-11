#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "RenderingUtils.h"
#include "MathUtils.h"

#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

//TODO: Mesh and materials should be loaded from a file and not set manually (custom JSON?)

class IRenderable
{
public:			
	void Initialize();
	void Render(GLenum renderMode = GL_TRIANGLES, bool renderWireframe = false);
	void Shutdown();	
	
	void ComputeMatrices()
	{
		const glm::mat4 trans = glm::translate(position_);
		const glm::mat4 scale = glm::scale(scale_);
		const glm::mat4 rot = glm::toMat4(rotation_);
		const glm::mat4 model = trans * rot * scale;

		const glm::mat4 proj = Camera::getInstance()->getProjectionMtx();
		const glm::mat4 view = Camera::getInstance()->getViewMtx();

		modelViewProjection_mtx_ = proj * view * model;
		viewModel_mtx_ = view * model;
	}

	const glm::mat4 getMVPmtx() const { return modelViewProjection_mtx_; }
	const glm::mat4 getModelmtx() const { return viewModel_mtx_; }
	const Material* getMaterial() const { return material_; }

protected:
	IRenderable();
	IRenderable(Mesh* mesh, Material* material);

	glm::vec3 position_ = glm::vec3();
	glm::vec3 scale_ = glm::vec3();
	glm::quat rotation_ = glm::quat();

	Mesh* mesh_ = nullptr;
	Material* material_ = nullptr;

private:
	GLuint vertexArrayObject_ = 0;
	GLuint vertexBuffer_ = 0;
	GLuint normalBuffer_ = 0;
	GLuint indexBuffer_ = 0;

	glm::mat4 modelViewProjection_mtx_ = glm::mat4(); 
	glm::mat4 viewModel_mtx_ = glm::mat4();
};
#endif