#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>
//#include "IRenderable.h"

class Light : public IRenderable
{
public:
	Light(glm::vec3 position = glm::vec3(0), glm::vec3 color = glm::vec3(255), float intensity = 1.0f) : IRenderable(false), intensity_(intensity), color_(color)
	{
		position_ = position;
	}

	const glm::vec3 getPosition() { return position_; }
	const glm::vec3 getColor() { return color_; }
	const float getIntensity() { return intensity_; }

private:
	glm::vec3 color_ = glm::vec3(255);
	float intensity_ = 1.0f;
};

#endif