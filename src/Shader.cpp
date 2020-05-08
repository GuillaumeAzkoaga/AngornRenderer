#include "Shader.h"
#include <fstream>
#include <sstream>
#include <Windows.h>



Shader::Shader(const GLenum type, const std::string name)
{
	CreateShader(type, name);
	CompileShader();
}

Shader::~Shader()
{
	glDeleteShader(shader_);
}

void Shader::CreateShader(const GLenum type, const std::string name)
{
	type_ = type;
	name_ = name;

	shader_ = glCreateShader(type_);

	if (shader_ == 0)
	{
		MessageBox(NULL, "Could not create shader", "Shader Creation Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
		return;
	}

	std::ifstream file(name);
	std::string shaderraw;

	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		shaderraw = buffer.str();
	}
	else
	{
		MessageBox(NULL, std::string("Could not load shader: " + name).c_str(), "Shader Loading Error",	MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
		file.close();
		return;
	}

	file.close();

	const GLchar* shadersource = shaderraw.c_str();
	glShaderSource(shader_, 1, &shadersource, NULL);
	glCheckError();
}

void Shader::CompileShader() const
{
	glCompileShader(shader_);

	GLint success = 0;
	glGetShaderiv(shader_, GL_COMPILE_STATUS, &success);
	glCheckError();

	if (success == GL_FALSE)
	{
		GLint loglength;
		glGetShaderiv(shader_, GL_INFO_LOG_LENGTH, &loglength);

		if (loglength > 0)
		{
			char* logdata = new char[loglength];
			GLsizei written;
			glGetShaderInfoLog(shader_, loglength, &written, logdata);
			MessageBox(NULL, logdata, "Shader Compilation Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
			delete[] logdata;
		}
	}
	
}

GLuint Shader::getShader() const
{
	return shader_;
}