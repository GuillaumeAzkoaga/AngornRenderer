#ifndef APPLICATION_H
#define APPLICATION_H

#include "ISystem.h"
#include "Ball.h"
#include "Light.h"

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

	//TODO: This should be handled by scene class
	const std::vector<Light*> getLights() const {return DEBUG_LIGHTS;}

private:
	Application(){}	

	void Initialize();
	void Update(float dt = 0);
	void Shutdown();

	void CreateScene();

	Ball* DEBUG_OBJECT = nullptr;
	//Light* DEBUG_LIGHT = nullptr;
	std::vector<Light*> DEBUG_LIGHTS;

	static Application* instance_;
	bool isRunning_ = false;
};

#endif