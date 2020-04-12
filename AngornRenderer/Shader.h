#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "RenderingUtils.h"

class Shader
{
public:
	Shader(const GLenum type, const std::string name);
	~Shader();

	GLuint getShader() const;

private:
	void CreateShader(const GLenum type, const std::string name);
	void CompileShader() const;

	GLuint shader_ = 0;
	GLenum type_ = 0;
	std::string name_;
};

#endif