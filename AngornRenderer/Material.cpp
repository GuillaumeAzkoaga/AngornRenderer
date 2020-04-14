#include "Material.h"

Material::Material(MATERIAL_TYPE type) : type_(type)
{
	switch (type)
	{
		case MATERIAL_TYPE::MAT_RUBY:
		{
			ambient_ = glm::vec3(0.1745, 0.01175, 0.01175);
			diffuse_ = glm::vec3(0.61424, 0.04136, 0.04136);
			specular_ = glm::vec3(0.727811, 0.626959, 0.626959);
			break;
		}
		case MATERIAL_TYPE::MAT_CHROME:
		{
			ambient_ = glm::vec3(0.0, 0.0, 0.0);
			diffuse_ = glm::vec3(0.55, 0.55, 0.55);
			specular_ = glm::vec3(0.70, 0.70, 0.70);
			break;
		}
		case MATERIAL_TYPE::MAT_NORMAL:
		{
			ambient_ = glm::vec3(0.0f, 0.0f, 0.0f);
			diffuse_ = glm::vec3(1.0f, 1.0f, 1.0f);
			specular_ = glm::vec3(1.0f, 1.0f, 1.0f);
			break;
		}

	}
}


MATERIAL_TYPE Material::getType() const
{
	return type_;
}

const glm::vec3& Material::getDiffuseColor() const
{
	return diffuse_;
}

const glm::vec3& Material::getAmbientColor() const
{
	return ambient_;
}

const glm::vec3& Material::getSpecularColor() const
{
	return specular_;
}

