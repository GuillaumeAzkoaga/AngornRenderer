#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glew.h>

class Shader
{
public:
	Shader(const GLenum type, const std::string name);
	~Shader();

	GLuint getShader() const;

private:
	void CreateShader(const GLenum type, const std::string name);
	void CompileShader() const;

	GLuint shader_;
	GLenum type_;
	std::string name_;
};

#endif