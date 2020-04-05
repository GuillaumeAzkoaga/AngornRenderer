#ifndef MATHUTILS_H_
#define MATHUTILS_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.1415926535897932384626433832795f
#define EPSILON 0.0001f
#define isZero(x) ((x < EPSILON) && (x > -EPSILON)) 


	/*glm::vec3 TEST_Normalize(const glm::vec3& v)
	{
		float length = glm::length(v);
		if (isZero(length))
		{
			return glm::vec3(0.0f);
		}

		return v / length;
	}

	glm::vec4 TEST_Normalize(const glm::vec4& v)
	{
		float length = glm::length(v);
		if (isZero(length))
		{
			return glm::vec4(0.0f);
		}

		return v / length;
	}*/


#endif