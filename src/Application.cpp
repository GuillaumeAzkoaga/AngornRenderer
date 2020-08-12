#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "ResourceLoader.h"
#include "FrameRateController.h"
#include "SceneManager.h"
#include "DiscordRichPresence.h"
#include "GUI.h"



Application* Application::instance_ = 0;

void Application::RunApplication(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle)
{
	RenderView::getInstance()->CreateMyWindow(hinstance, show, WindowWidth, WindowHeight, WindowTitle);	
	Camera::getInstance()->CreateCamera(glm::vec3(-1000.0f, 0.0f, 0.0f));

	Initialize();
	Update();
	Shutdown();
}

void Application::ExitApplication()
{
	Shutdown();
}


void Application::Initialize()
{
	RenderView::getInstance()->Initialize();	
	InputManager::getInstance()->Initialize();	
	Camera::getInstance()->Initialize();
	Renderer::getInstance()->Initialize();
	SceneManager::getInstance()->SetScene("../Data/Scenes/Default.json");
	GUI::getInstance()->Initialize();

	#if DISCORD_ENABLED
		DiscordRichPresence::getInstance()->Initialize();
	#endif
}

void Application::Update(float dt)
{
	while (isRunning_)
	{
		FrameRateController::getInstance()->StartFrame();

		dt = static_cast<float>(FrameRateController::getInstance()->getCurrentFrameTime());
		InputManager::getInstance()->Update(dt);

		if (InputManager::getInstance()->KeyIsTriggered(VK_ESCAPE))
			isRunning_ = false;
		else if (InputManager::getInstance()->KeyIsTriggered(VK_NUMPAD1))
			SceneManager::getInstance()->SetScene("../Data/Scenes/Default.json");
		else if (InputManager::getInstance()->KeyIsTriggered(VK_NUMPAD2))
			SceneManager::getInstance()->SetScene("../Data/Scenes/Default2.json");

		RenderView::getInstance()->Update(dt);
		Camera::getInstance()->Update(dt);
		Renderer::getInstance()->Update(dt);

		#if DISCORD_ENABLED
			DiscordRichPresence::getInstance()->Update(dt);
		#endif		

		FrameRateController::getInstance()->EndFrame();
	}
}

void Application::Shutdown()
{		
	#if DISCORD_ENABLED
		DiscordRichPresence::getInstance()->Shutdown();
	#endif
	Renderer::getInstance()->Shutdown();
	Camera::getInstance()->Shutdown();
	InputManager::getInstance()->Shutdown();
	RenderView::getInstance()->Shutdown();

	isRunning_ = false;
}



