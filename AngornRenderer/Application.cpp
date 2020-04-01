#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Camera.h"

Application* Application::instance_ = 0;



void Application::RunApplication(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle)
{
	RenderView::getInstance()->CreateMyWindow(hinstance, show, WindowWidth, WindowHeight, WindowTitle);	
	Camera::getInstance()->CreateCamera(glm::vec3(-1000.0f, 0.0f, 0.0f));

	Initialize();
	Update();
	Shutdown();
}

void Application::Initialize()
{
	isRunning_ = true;
	RenderView::getInstance()->Initialize();	
	InputManager::getInstance()->Initialize();	
	Camera::getInstance()->Initialize();
	Renderer::getInstance()->Initialize();
}

void Application::Update(float dt)
{
	while (isRunning_)
	{
		InputManager::getInstance()->Update(dt);
		RenderView::getInstance()->Update(dt);
		Camera::getInstance()->Update(dt);
		Renderer::getInstance()->Update();

		if (InputManager::getInstance()->KeyIsTriggered(VK_ESCAPE))
			isRunning_ = false;		
	}
}

void Application::Shutdown()
{		
	Renderer::getInstance()->Shutdown();
	Camera::getInstance()->Shutdown();
	InputManager::getInstance()->Shutdown();
	RenderView::getInstance()->Shutdown();

	isRunning_ = false;
}

