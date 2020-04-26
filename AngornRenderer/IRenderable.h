#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include "RenderingUtils.h"
#include "MathUtils.h"

#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
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
	const Texture* getTexture() const { return texture_; }

protected:
	IRenderable(bool toRender = true);
	IRenderable(Mesh* mesh, Material* material, bool toRender = true);
	IRenderable(Mesh* mesh, Texture* texture, bool toRender = true);

	glm::vec3 position_ = glm::vec3();
	glm::vec3 scale_ = glm::vec3();
	glm::quat rotation_ = glm::quat();

	Mesh* mesh_ = nullptr;
	Material* material_ = nullptr;
	Texture* texture_ = nullptr;
private:
	GLuint vertexArrayObject_ = 0;
	GLuint vertexBuffer_ = 0;
	GLuint normalBuffer_ = 0;
	GLuint textCoordBuffer_ = 0;
	GLuint indexBuffer_ = 0;
};
#endif