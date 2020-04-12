#include "ShaderProgram.h"

#include <Windows.h>
#include "MathUtils.h"

ShaderProgram::ShaderProgram()
{
	program_ = glCreateProgram();
	if (program_ == 0)	
		MessageBox(NULL, "Error creating shader program", "OpenGL program creation error",	MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);

	glCheckError();
}

ShaderProgram::~ShaderProgram()
{
	glUseProgram(0);
	glDeleteProgram(program_);
}

void ShaderProgram::AttachShader(const Shader * shader)
{
	glAttachShader(program_, shader->getShader());
	glCheckError();
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(program_);
	glCheckError();

	GLint status;
	//glGetShaderiv(program_, GL_LINK_STATUS, &status);
	glGetProgramiv(program_, GL_LINK_STATUS, &status);
	glCheckError();

	if (status == GL_FALSE)
	{
		GLint loglength;
		glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &loglength);		

		if (loglength > 0)
		{
			char* logdata = new char[loglength];
			GLsizei written;
			glGetProgramInfoLog(program_, loglength, &written, logdata);
			MessageBox(NULL, written > 0 ? logdata : "ERROR", "Shader Program Linking Error",
				MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
			delete[] logdata;
		}
	}
}

void ShaderProgram::UseProgram()
{
	glUseProgram(program_);
	glCheckError();
}

GLuint ShaderProgram::getUniform(const std::string name)
{
	auto it = uniforms_.find(name);

	if (it != uniforms_.end())
	{
		return it->second;
	}
	else
	{
		const GLuint toreturn = glGetUniformLocation(program_, name.c_str());

		if (toreturn == -1)
			return toreturn;

		uniforms_[name] = toreturn;
		return toreturn;
	}
}

void ShaderProgram::setUniform(const std::string name, const glm::mat3 value, GLboolean transpose)
{
	glUniformMatrix3fv(getUniform(name), 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string name, const glm::mat4 value, GLboolean transpose)
{
	glUniformMatrix4fv(getUniform(name), 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string name, const glm::vec3 value)
{
	glUniform3fv(getUniform(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string name, const glm::vec4 value)
{
	glUniform4fv(getUniform(name), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const std::string name, int value)
{
	glUniform1i(getUniform(name), value);
}

void ShaderProgram::setUniform(const std::string name, unsigned value)
{
	glUniform1ui(getUniform(name), value);
}

void ShaderProgram::setUniform(const std::string name, float value)
{
	glUniform1f(getUniform(name), value);
}
