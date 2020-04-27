#include "Application.h"

//TODO: why are we not outputting to error log anymore??(check git history)
//TODO: Have a default shader in case one couldn't be loaded or compiled
//TODO: Discord Rich presence https://discordapp.com/developers/docs/rich-presence/how-to
int WINAPI WinMain(HINSTANCE instance, HINSTANCE hPreviousInstance, LPSTR, int show)
{
	SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);

	Application::getInstance()->RunApplication(instance, show, 1280, 720, "AngornRenderer");

	return 0;
}

