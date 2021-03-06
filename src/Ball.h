#ifndef BALL_H_
#define BALL_H_

#include "IRenderable.h"
#include "ResourceLoader.h"

class Ball : public IRenderable
{
public:
	Ball(glm::vec3 position, glm::vec3 scale, glm::quat rotation, Material* material)
	{
		mesh_ = ResourceLoader::getInstance()->getMesh("../Data/Meshes/sphere_8_4.obj");
		material_ = material;
		position_ = position;
		scale_ = scale;
		rotation_ = rotation;		
	}
};

#endif