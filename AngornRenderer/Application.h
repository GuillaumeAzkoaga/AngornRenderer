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

	void RunApplication(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle);
	void ExitApplication();
	

private:
	Application(){}	

	void Initialize();
	void Update(float dt = 0);
	void Shutdown();
	
	static Application* instance_;
	bool isRunning_ = true;
};

#endif