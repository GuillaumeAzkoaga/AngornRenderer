#include "Renderer.h"
#include "RenderView.h"

#include <glew.h>
#include <wglew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <cstdio>
Renderer* Renderer::instance_ = 0;

void Renderer::Initialize()
{
	deviceContext_ = GetDC(RenderView::getInstance()->getHandle());

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
	int nPixelFormat = ChoosePixelFormat(deviceContext_, &pfd);
	if (!SetPixelFormat(deviceContext_, nPixelFormat, &pfd))
	{
		MessageBox(RenderView::getInstance()->getHandle(), "SetPixelFormat Error", "OpenGL Initialization Error", MB_ICONERROR);
		ExitProcess(1);
	}

	// Create fake context
	HGLRC tempContext = wglCreateContext(deviceContext_);
	wglMakeCurrent(GetDC(RenderView::getInstance()->getHandle()), tempContext);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		MessageBox(NULL, "GLEW failed to initialize", " GLEW Initialization Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
		ExitProcess(0);
	}


	// Define context attributes
	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, glMajorVersion_,
		WGL_CONTEXT_MINOR_VERSION_ARB, glMinorVersion_,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0
	};

	// Check that GLEW is supported
	if (wglewIsSupported("WGL_ARB_create_context") == 1)
	{
		// Create a new context and delete the temporary one
		renderContext_ = wglCreateContextAttribsARB(deviceContext_, 0, attribs);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);
		wglMakeCurrent(deviceContext_, renderContext_);
	}

	// Check for valid OpenGL version
	char strError[20];
	sprintf_s(strError, "GL_VERSION_%d_%d", glMajorVersion_, glMinorVersion_);
	if (!glewIsSupported(strError))
	{
		char sErrorMessage[255], sErrorTitle[255];
		sprintf_s(sErrorMessage, "OpenGL %d.%d is not supported! Please download latest GPU drivers!", glMajorVersion_, glMinorVersion_);
		sprintf_s(sErrorTitle, "OpenGL %d.%d Not Supported", glMajorVersion_, glMinorVersion_);
		MessageBox(RenderView::getInstance()->getHandle(), sErrorMessage, sErrorTitle, MB_ICONINFORMATION);
		ExitProcess(0);
	}

	glViewport(0, 0, RenderView::getInstance()->getWidth(), RenderView::getInstance()->getHeight());

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	//TODO: Initialize render passes
	//TODO: Create the ToRenderQuad
}

void Renderer::Update(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TODO: Apply render passes

	glUseProgram(0);
	glBindBuffer(GL_FRAMEBUFFER, 0);
	glFlush();
	glFinish();

	SwapBuffers(deviceContext_);
}

void Renderer::Shutdown()
{
	//TODO:Shutdown render passes

	wglMakeCurrent(NULL, NULL);
	if (renderContext_)
	{
		wglDeleteContext(renderContext_);
		renderContext_ = NULL;
	}
}

Shader * Renderer::getShader(const GLenum shaderType, const std::string shaderName)
{
	Shader* shader = nullptr;	

	auto it = shaders_.find(shaderName);
	if (it == shaders_.end())	
		shader = new Shader(shaderType, shaderName); //The shader was not yet loaded so it needs to be created & compiled
	else
		shader = it->second; //Already loaded

	return shader;
}
