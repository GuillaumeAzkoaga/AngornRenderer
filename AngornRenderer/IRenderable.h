#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "RenderingUtils.h"
#include "MathUtils.h"

#include "Material.h"
#include "Mesh.h"

class IRenderable
{
public:
	IRenderable() {}

	void Initialize();
	void Render(GLenum renderMode = GL_TRIANGLES);
	void Shutdown();

	//TODO: Mesh and materials should be loaded from a file and not set manually (custom JSON?)
	void setMesh(Mesh* mesh) { mesh_ = mesh; }
	//void setMaterial(Material* material) { material_ = material; }

	const glm::mat4 getPositionMtx() const { return glm::translate(position_); }
	const glm::mat4 getScaleMtx() const { return glm::scale(scale_); }
	const glm::mat4 getRotationMtx() const { return glm::toMat4(rotation_); }

private:
	Mesh* mesh_ = nullptr;
	//Material* material_ = nullptr;

	glm::vec3 position_ = glm::vec3();
	glm::vec3 scale_ = glm::vec3();
	glm::quat rotation_ = glm::quat();

	GLuint vertexArrayObject_ = 0;
	GLuint vertexBuffer_ = 0;
	GLuint normalBuffer_ = 0;
	GLuint indexBuffer_ = 0;

};
#endif