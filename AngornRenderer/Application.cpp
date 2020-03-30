#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"
#include "Renderer.h"

Application* Application::instance_ = 0;



void Application::RunApplication(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle)
{
	RenderView::getInstance()->CreateMyWindow(hinstance, show, WindowWidth, WindowHeight, WindowTitle);	

	Initialize();
	Update();
	Shutdown();
}

void Application::Initialize()
{
	isRunning_ = true;
	RenderView::getInstance()->Initialize();	
	InputManager::getInstance()->Initialize();	
	Renderer::getInstance()->Initialize();
}

void Application::Update(float dt)
{
	while (isRunning_)
	{
		InputManager::getInstance()->Update(dt);
		RenderView::getInstance()->Update(dt);
		//TODO: Update camera before render
		Renderer::getInstance()->Update();

		if (InputManager::getInstance()->KeyIsTriggered(VK_ESCAPE))
			isRunning_ = false;		
	}
}

void Application::Shutdown()
{	
	RenderView::getInstance()->Shutdown();
	InputManager::getInstance()->Shutdown();
	Renderer::getInstance()->Shutdown();
	isRunning_ = false;
}

