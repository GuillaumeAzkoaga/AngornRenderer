#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <map>
#include <string>
#include <glm/glm.hpp>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void AttachShader(const Shader* shader);

	void LinkProgram();
	void UseProgram();


	GLuint getUniform(const std::string name);

	void setUniform(const std::string name, const glm::mat3 value, GLboolean transpose = GL_FALSE);
	void setUniform(const std::string name, const glm::mat4 value, GLboolean transpose = GL_FALSE);
	void setUniform(const std::string name, const glm::vec3 value);
	void setUniform(const std::string name, const glm::vec4 value);
	void setUniform(const std::string name, int value);
	void setUniform(const std::string name, unsigned value);
	void setUniform(const std::string name, float value);

private:
	GLuint program_;

	std::map<std::string, GLuint> uniforms_;
};

#endif