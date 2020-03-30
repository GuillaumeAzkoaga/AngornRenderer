#ifndef RENDERER_H_
#define RENDERER_H_

#include "ISystem.h"

#include <Windows.h>

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

private:
	Renderer() {}
	static Renderer* instance_;

	HDC deviceContext_;
	HGLRC renderContext_;

	int glMajorVersion_ = 4;
	int glMinorVersion_ = 2;
};
#endif