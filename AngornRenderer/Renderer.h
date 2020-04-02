#ifndef RENDERER_H_
#define RENDERER_H_

#include "ISystem.h"
#include "Shader.h"

#include <Windows.h>
#include <map>
#include <string>

class Renderer : public ISystem
{
public:
	static Renderer* getInstance()
	{
		if (!instance_)
			instance_ = new Renderer();
		return instance_;
	}

	void Initialize();
	void Update(float dt = 0);
	void Shutdown();

	/// <summary>
	/// Returns the shader matching the provided type and name.
	/// If the shader is not found among the loaded shaders, it will be created and compiled
	/// </summary>
	/// <param name="shaderType">[GLenum] shader type</param>
	/// <param name="shaderName"></param>
	/// <returns></returns>
	Shader* getShader(const GLenum shaderType, const std::string shaderName);
private:
	Renderer() {}
	static Renderer* instance_;

	HDC deviceContext_ = 0;
	HGLRC renderContext_ = 0;

	int glMajorVersion_ = 4;
	int glMinorVersion_ = 2;

	std::map<std::string, Shader*> shaders_;

};
#endif