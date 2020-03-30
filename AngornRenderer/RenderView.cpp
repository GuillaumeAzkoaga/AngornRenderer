#include "RenderView.h"
#include "InputManager.h"
#include "Application.h"

RenderView* RenderView::instance_ = 0;

void RenderView::CreateMyWindow(HINSTANCE hinstance, int show, int WindowWidth, int WindowHeight, const char * WindowTitle)
{
	handle_ = NULL;
	hInstance_ = NULL;
	// create a window class and fill it up with the appropriate parameters
	// http://msdn.microsoft.com/en-us/library/ms633577.aspx

	// Store the window width & height
	width_ = WindowWidth;
	height_ = WindowHeight;

	class_.cbSize = sizeof(WNDCLASSEX);					// The default size of our window class structure
	class_.style = CS_HREDRAW | CS_VREDRAW;				// the style of the window
	class_.lpfnWndProc = MessageHandler;					// Pointer to our message handler function (declared above, but defined below)
	class_.cbClsExtra = 0;									// The number of extra bytes you want to allocate for this window class structure. the default is 0
	class_.cbWndExtra = 0;									// The number of extra bytes you want to allocate for the window instance.
	class_.hInstance = hinstance;							// Handle to the instance that contains the window procedure for the class
	class_.hIcon = NULL;									// Let the system provide the default icon.
	class_.hCursor = LoadCursor(NULL, IDC_ARROW);		// Use default cursor. The value of hinstance in that function is null in order to use one of the predefined cursors.
	class_.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// Handle tot eh calss background brush. It can be used as a color
	class_.lpszMenuName = NULL;								// No menu for that window
	class_.hIconSm = NULL;								// A handle to a small icon that is associated with the window class. We will use the same icon as the default one.
	class_.lpszClassName = WindowTitle;							// A string that specifies the window class name. The name must be less than 255.

	// Register the class - Show a message if the registration failed
	if (!RegisterClassEx(&class_))
	{
		MessageBox(NULL, "Call to RegisterClassEx Failed", "", NULL);
		return;
	}

	// IMPORTANT STEP - The width you pass to the create window function is 
	// the width of the window including the title bar and the borders
	// to get the actual size of a window given the desired CLIENT area
	// use AdjustWindowRect function 
	// http://msdn.microsoft.com/en-us/library/ms632665(v=vs.85).aspx
	RECT winrect = { 0,0,WindowWidth, WindowHeight };
	AdjustWindowRect(&winrect, WS_OVERLAPPEDWINDOW, FALSE);

	// Register was successful->Create the window - http://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx
	handle_ = CreateWindow(
		WindowTitle,			// The name of the window class - we used the same name as the window title 
		WindowTitle,			// The window title - This will appear in the title bar and can be changed at run time
		WS_OVERLAPPEDWINDOW,	// The style of the window, this will create a classic window, see msdn for more styles
		0,						// POSITION of the window
		0,						// POSITION of the window
		winrect.right - winrect.left,	// Width of the window in window size NOT client size
		winrect.bottom - winrect.top,	// Height of the windowin window size NOT client size
		NULL,					// Parent Window
		NULL,					// Handle to the menu
		hinstance,				// Instance of the application to be associated with that window
		NULL);					// Pointer to the value to be passed to the window when it's created and when it receives the WM_CREATE message. No need here.

	// NOTE: If the window was not created successfully, then the handle returned by CreateWindow should be null. 

	// Post an error message if the window was not created successfully
	if (!handle_)
	{
		MessageBox(NULL, "Failed to Create the window!", "", NULL);
		return;
	}

	// Creating the window was successful -> Show the window
	ShowWindow(handle_, show);
	UpdateWindow(handle_);				// Updates the clien area of the window by sending a paint message to the window.

	// Keep a copy of the App Instance for unregistering the class
	hInstance_ = hinstance;


}

void RenderView::Initialize()
{
}

void RenderView::Update(float dt)
{
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void RenderView::Shutdown()
{
	UnregisterClass(class_.lpszClassName, hInstance_);
}

LRESULT RenderView::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC dc;
	PAINTSTRUCT ps;


	if (InputManager::getInstance()->HandleInputMessage(hWnd, msg, wParam, lParam))
		return 0;

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		Application::getInstance()->Exit();
		break;
	case WM_CREATE:
		break;

	case WM_PAINT:
		dc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_MOVE:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return 0;
}

HWND RenderView::getHandle(void)
{
	return handle_;
}

int RenderView::getWidth(void)
{
	return width_;
}

int RenderView::getHeight(void)
{
	return height_;
}

void RenderView::setPosition(float x, float y)
{
	SetWindowPos(handle_, NULL,
		(int)x,
		(int)y,
		(int)width_,
		(int)height_,
		SWP_SHOWWINDOW | SWP_NOSIZE);
}

void RenderView::setFullscreen(bool fullscreen)
{
	RECT winrect = { 0,0, (LONG)width_, (LONG)height_ };

	if (fullscreen)
	{
		SetWindowLong(handle_, GWL_STYLE, WS_POPUP | WS_SYSMENU | WS_VISIBLE);
		AdjustWindowRect(&winrect, WS_POPUP | WS_SYSMENU | WS_VISIBLE, FALSE);


	}
	else
	{
		SetWindowLong(handle_, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		AdjustWindowRect(&winrect, WS_BORDER, FALSE);
	}



	SetWindowPos(
		handle_,		// handle to our window
		NULL,				// handle of the window to insert after - ignored
		0,					// x POSITION (this will be ignored)
		0,					// y POSITION (this will be ignored)
		winrect.right - winrect.left,					// new width of the window
		winrect.bottom - winrect.top,					// new height of the window
		SWP_SHOWWINDOW			// flags: in this case just ignore the POSITION
	);
}

void RenderView::setSize(float w, float h)
{
	width_ = (int)w;
	height_ = (int)h;

	RECT winrect = { 0,0, (LONG)width_, (LONG)height_ };

	AdjustWindowRect(&winrect, WS_POPUP | WS_SYSMENU | WS_VISIBLE, FALSE);



	SetWindowPos(
		handle_,		// handle to our window
		NULL,				// handle of the window to insert after - ignored
		0,					// x POSITION (this will be ignored)
		0,					// y POSITION (this will be ignored)
		winrect.right - winrect.left,					// new width of the window
		winrect.bottom - winrect.top,					// new height of the window
		SWP_SHOWWINDOW			// flags: in this case just ignore the POSITION
	);
}

void RenderView::setCursorPosition(float x, float y)
{
	POINT p;
	p.x = (LONG)(width_ / 2.0f + x);
	p.y = (LONG)(height_ / 2.0f + y);
	ClientToScreen(handle_, &p);
	SetCursorPos(p.x, p.y);
}

void RenderView::setCursorVisibility(bool show)
{
	ShowCursor(show);
}
