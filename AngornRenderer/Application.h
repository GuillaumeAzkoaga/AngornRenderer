#ifndef APPLICATION_H
#define APPLICATION_H

#include "ISystem.h"

#include <Windows.h>

class Application : public ISystem
{
public:
	static Application* getInstance()
	{
		if (!instance_)
			instance_ = new Application();
		return instance_;
	}

	Application(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle);
	void Initialize();
	void Update(float dt = 0);
	void Shutdown();
	void Exit();



private:
	Application(){}
	
	static Application* instance_;

	bool isRunning_ = false;
};

#endif