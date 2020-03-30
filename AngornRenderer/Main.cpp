#include "Application.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR, int show)
{
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	Application * app = new Application(instance, show, 1280, 720, "AngornRenderer");
	
	app->Initialize();
	app->Update();
	app->Shutdown();

	delete app;

	return 0;
}
