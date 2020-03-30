#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"

Application* Application::instance_ = 0;

Application::Application(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle)
{
	RenderView::getInstance()->CreateMyWindow(hinstance, show, WindowWidth, WindowHeight, WindowTitle);
	isRunning_ = false;
}

void Application::Initialize()
{
	RenderView::getInstance()->Initialize();	
	InputManager::getInstance()->Initialize();
}

void Application::Update(float dt)
{
	while (!isRunning_)
	{
		InputManager::getInstance()->Update();
		RenderView::getInstance()->Update();

		if (InputManager::getInstance()->KeyIsTriggered(VK_ESCAPE))
			isRunning_ = true;

		//TODO:
		//dt = (float)(frc_->GetFrameTime());
	}
}

void Application::Shutdown()
{
	RenderView::getInstance()->Shutdown();
	InputManager::getInstance()->Shutdown();
}

void Application::Exit()
{
	isRunning_ = true;
}
