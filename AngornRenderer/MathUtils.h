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

#endif