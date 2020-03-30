#include "Application.h"

//TODO: Store loaded shaders in Graphics Manager
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR, int show)
{
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	Application::getInstance()->RunApplication(instance, show, 1280, 720, "AngornRenderer");
	
	return 0;
}
