#ifndef WINDOW_MANAGER_H_
#define WINDOW_MANAGER_H_

#include <Windows.h>

#include "ISystem.h"


class RenderView : public ISystem
{
public:
	static RenderView* getInstance()
	{
		if (!instance_)
			instance_ = new RenderView();

		return instance_;
	}

	void CreateMyWindow(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle);
	
	void Initialize();
	void Update(float dt = 0);
	void Shutdown();
	
	static LRESULT CALLBACK MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND getHandle(void);
	int getWidth(void);
	int getHeight(void);	

	void setPosition(float x, float y);
	void setFullscreen(bool fullscreen);
	void setSize(float w, float h);

	void setCursorPosition(float x, float y);
	void setCursorVisibility(bool show);

private:	
	RenderView() {};
	static RenderView* instance_;

	HWND handle_ = 0;
	WNDCLASSEX class_ = {};
	HINSTANCE hInstance_ = 0;
	int width_ = 0;
	int height_= 0;
};

#endif // ! WINDOW_MANAGER_H_
