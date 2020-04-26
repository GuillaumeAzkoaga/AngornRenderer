#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "ResourceLoader.h"
#include "FrameRateController.h"

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

	CreateScene();
	Renderer::getInstance()->Initialize();

	
}

void Application::Update(float dt)
{
	while (isRunning_)
	{
		FrameRateController::getInstance()->StartFrame();

		dt = static_cast<float>(FrameRateController::getInstance()->getCurrentFrameTime());
		InputManager::getInstance()->Update(dt);
		RenderView::getInstance()->Update(dt);
		Camera::getInstance()->Update(dt);
		Renderer::getInstance()->Update(dt);

		if (InputManager::getInstance()->KeyIsTriggered(VK_ESCAPE))
			isRunning_ = false;	

		FrameRateController::getInstance()->EndFrame();
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

//TODO: Create a scene class
void Application::CreateScene()
{
	Camera::getInstance()->CreateCamera(glm::vec3(-1000.f, 0.0f, 0.0f));

	DEBUG_OBJECT = new Ball(glm::vec3(0, 0, 0), glm::vec3(200), glm::angleAxis(0.0f, glm::vec3(1, 0, 0)), ResourceLoader::getInstance()->getMaterial(MATERIAL_TYPE::MAT_RUBY));
	Texture* test = ResourceLoader::getInstance()->getTexture("Earth", "..//Textures//container.jpg");
	DEBUG_OBJECT_TEXTURES = new Ball(glm::vec3(0, 0, -500), glm::vec3(100), glm::angleAxis(0.0f, glm::vec3(1, 0, 0)), test/*ResourceLoader::getInstance()->getMaterial(MATERIAL_TYPE::MAT_RUBY)*/);

	DEBUG_LIGHTS.push_back(new Light(glm::vec3(0, 500, 0), glm::vec3(1)));
}

