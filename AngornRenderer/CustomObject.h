#ifndef CUSTOM_OBJECT_H_
#define CUSTOM_OBJECT_H_
#include "IRenderable.h"

class CustomObject : public IRenderable
{
public:
	CustomObject(glm::vec3 position, glm::vec3 scale, glm::quat rotation,Mesh* mesh, Material* material) {
		mesh_ = mesh;
		material_ = material;
		position_ = position;
		scale_ = scale;
		rotation_ = rotation;
	}

};


#endif