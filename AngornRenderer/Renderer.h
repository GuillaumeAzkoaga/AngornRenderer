#ifndef RENDERER_H_
#define RENDERER_H_

#include "ISystem.h"
#include "IRenderable.h"
#include "Shader.h"
#include "GBuffer.h"

#include "GeometryPass.h"

#include <Windows.h>
#include <map>
#include <vector>
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

	std::vector<IRenderable*> getRenderables() const;
	void RegisterRenderable(IRenderable* object);

	void RegisterBuffer(const std::string bufferName, GBuffer* gbuffer);
	GBuffer* getBuffer(const std::string bufferName) const;

private:
	Renderer() {}
	static Renderer* instance_;

	HDC deviceContext_ = 0;
	HGLRC renderContext_ = 0;

	int glMajorVersion_ = 4;
	int glMinorVersion_ = 0;

	std::map<std::string, Shader*> shaders_;
	std::map<std::string, GBuffer*> buffers_;
	std::vector<IRenderable*> renderables_;

	GeometryPass* GeometryPass_ = nullptr;
};
#endif