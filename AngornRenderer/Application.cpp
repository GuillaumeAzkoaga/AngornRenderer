#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "ResourceLoader.h"

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

//TODO: Create a scene class
void Application::CreateScene()
{
	Camera::getInstance()->CreateCamera(glm::vec3(-1000.f, 0.0f, 0.0f));

	DEBUG_OBJECT = new Ball(glm::vec3(0, 50, 0), glm::vec3(500), glm::angleAxis(0.0f, glm::vec3(1, 0, 0)), new Material(MATERIAL_TYPE::MAT_RUBY));
	DEBUG_LIGHTS.push_back(new Light(glm::vec3(0, 500, 0), glm::vec3(1)));
}

