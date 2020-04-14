#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "RenderingUtils.h"
#include "MathUtils.h"

#include "Material.h"
#include "Mesh.h"
#include "ShaderProgram.h"

//TODO: Mesh and materials should be loaded from a file and not set manually (custom JSON?)

class IRenderable
{
public:			
	void Initialize();
	void Render(GLenum renderMode = GL_TRIANGLES, bool renderWireframe = false);
	void Shutdown();	
	
	const glm::mat4 getModelMatrix() const 
	{ 
		const glm::mat4 trans = glm::translate(position_);
		const glm::mat4 scale = glm::scale(scale_);
		const glm::mat4 rot = glm::toMat4(rotation_);
		return  trans * rot * scale;
	}
	const Material* getMaterial() const { return material_; }

protected:
	IRenderable(bool toRegister = true);
	IRenderable(Mesh* mesh, Material* material, bool toRegister = true);

	glm::vec3 position_ = glm::vec3();
	glm::vec3 scale_ = glm::vec3();
	glm::quat rotation_ = glm::quat();

	Mesh* mesh_ = nullptr;
	Material* material_ = nullptr;

private:
	GLuint vertexArrayObject_ = 0;
	GLuint vertexBuffer_ = 0;
	GLuint normalBuffer_ = 0;
	GLuint textCoordBuffer_ = 0;
	GLuint indexBuffer_ = 0;
};
#endif