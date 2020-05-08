#ifndef MATERIAL_H
#define MATERIAL_H

#include "MathUtils.h"

enum class MATERIAL_TYPE
{	
	MAT_NORMAL,
	MAT_CHROME,
	MAT_RUBY,
	MATERIAL_NUM
};


class Material
{
public:
	Material(MATERIAL_TYPE type);

	const glm::vec3& getDiffuseColor() const;
	const glm::vec3& getAmbientColor() const;
	const glm::vec3& getSpecularColor() const;
	MATERIAL_TYPE getType() const;

private:
	glm::vec3 diffuse_;
	glm::vec3 ambient_;
	glm::vec3 specular_;
	MATERIAL_TYPE type_;
};

#endif