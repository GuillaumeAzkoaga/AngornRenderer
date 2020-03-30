#include "Application.h"
#include "RenderView.h"
#include "InputManager.h"

#pragma region TO_CLEAN_TO_GRAPHICS_FILE
#include <glew.h>
#include <wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma endregion



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

#pragma region TO_CLEAN_TO_GRAPHICS_FILE

	HDC deviceContext = GetDC(RenderView::getInstance()->getHandle());

	// Define pixel format options
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;
	// Set pixel format
	int nPixelFormat = ChoosePixelFormat(deviceContext, &pfd);
	if (!SetPixelFormat(deviceContext, nPixelFormat, &pfd))
	{
		MessageBox(RenderView::getInstance()->getHandle(), "SetPixelFormat Error", "OpenGL Initialization Error", MB_ICONERROR);
		ExitProcess(1);
	}

	// Create fake context
	HGLRC tempContext = wglCreateContext(deviceContext);
	wglMakeCurrent(GetDC(RenderView::getInstance()->getHandle()), tempContext);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		MessageBox(NULL, "GLEW failed to initialize", " GLEW Initialization Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
		ExitProcess(0);
	}
	

	// Define context attributes
	const int glMajorVersion = 4;
	const int glMinorVersion = 2;
	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, glMajorVersion,
		WGL_CONTEXT_MINOR_VERSION_ARB, glMinorVersion,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0
	};

	// Check that GLEW is supported
	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		// Create a new context and delete the temporary one
		HGLRC renderContext = wglCreateContextAttribsARB(deviceContext, 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(deviceContext, renderContext);
	}

	// Check for valid OpenGL version
	char strError[20];
	sprintf_s(strError, "GL_VERSION_%d_%d", glMajorVersion, glMinorVersion);
	if (!glewIsSupported(strError))
	{
		char sErrorMessage[255], sErrorTitle[255];
		sprintf_s(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!", glMajorVersion, glMinorVersion);
		sprintf_s(sErrorTitle, "OpenGL %d.%d Not Supported", glMajorVersion, glMinorVersion);
		MessageBox(RenderView::getInstance()->getHandle(), sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
		ExitProcess(0);
	}

	glViewport(0, 0, RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
#pragma endregion

}

void Application::Update(float dt)
{
	while (isRunning_)
	{
		InputManager::getInstance()->Update(dt);
		RenderView::getInstance()->Update(dt);

		if (InputManager::getInstance()->KeyIsTriggered(VK_ESCAPE))
			isRunning_ = false;		
	}
}

void Application::Shutdown()
{	
	RenderView::getInstance()->Shutdown();
	InputManager::getInstance()->Shutdown();
	isRunning_ = false;
}

