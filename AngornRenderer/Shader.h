#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glew.h>

class Shader
{
public:
	enum ShaderType
	{
		ST_Vertex,
		ST_TessControl,
		ST_TessEval,
		ST_Geometry,
		ST_Fragment,
		ST_AMOUNT
	};

	Shader();
	~Shader();

	bool CreateShader(GLenum type, const std::string& name);
	bool CompileShader();

	GLuint GetShader() const;

private:
	GLuint shader_;
	GLenum type_;
	std::string name_;
};

#endif