#ifndef RENDERER_H_
#define RENDERER_H_

#include "ISystem.h"

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

};
#endif