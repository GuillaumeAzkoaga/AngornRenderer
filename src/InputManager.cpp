#include "InputManager.h"
#include "RenderView.h"
#include "AntTweakBar/AntTweakBar.h"

InputManager* InputManager::instance_ = 0;

void InputManager::Initialize()
{
	memset(currentKey_, 0, 256);
	memset(previousKey_, 0, 256);

	memset(currentMouseButton_, 0, 2);
	memset(previousMouseButton_, 0, 2);

}

bool InputManager::HandleInputMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (TwEventWin(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
		// Key pressed
		case WM_KEYDOWN:
		{
			currentKey_[wParam] = 1;
			break;
		}
		// Key released
		case WM_KEYUP:
		{
			currentKey_[wParam] = 0;
		}
		// Left mouse button pressed
		case WM_LBUTTONDOWN:
		{
			currentMouseButton_[MOUSE_LEFT] = 1;
			break;
		}
		// Left mouse button released
		case WM_LBUTTONUP:
		{
			currentMouseButton_[MOUSE_LEFT] = 0;
			break;
		}
		// Right mouse button pressed
		case WM_RBUTTONDOWN:
		{
			currentMouseButton_[MOUSE_RIGHT] = 1;
			break;
		}
		// Right mouse button released
		case WM_RBUTTONUP:
		{
			currentMouseButton_[MOUSE_RIGHT] = 0;
			break;
		}
		default:
			return false;

	}

	return true;

}


void InputManager::Update(float dt)
{
	RenderView* pWindow = RenderView::getInstance();

	POINT pos; // Windows point
	GetCursorPos(&pos); // Get the cursor POSITION in the screen
	ScreenToClient(pWindow->getHandle(), &pos); // Convert the POSITION into window POSITION
	

	// Convert the window POSITION into window centered
	mousePos_.x = ((float)(pos.x - pWindow->getWidth() / 2));
	mousePos_.y = ((float)(-pos.y + pWindow->getHeight() / 2));

	// Check if the POSITION on the screen is outside the window
	if (pos.x >= pWindow->getWidth() || pos.x <= 0
		|| pos.y >= pWindow->getHeight() || pos.y <= 0)
	{
		isMouseWithinWindow_ = false; // Set inside window to false
	}
	else
	{
		isMouseWithinWindow_ = true; // Set inside window to true
	}

	// Go through all the keys
	for (int i = 0; i < 256; i++)
	{
		// If the corresponding key is pressed or triggered
		if (currentKey_[i])
		{
			// Check if it was not pressed
			if (previousKey_[i] == 0)
				currentKey_[i] = 2; // Set key to triggered			
			else
				currentKey_[i] = 1; // Set key to pressed

		}

		previousKey_[i] = currentKey_[i]; // Set the current value in the previous
	}

	// Go through all the mouse buttons
	for (int i = 0; i < 2; i++)
	{
		// If the corresponding button is pressed or triggered
		if (currentMouseButton_[i]/* == 1 || CurrentMouseButton[i] == 2*/)
		{
			// Check if it was not pressed
			if (previousMouseButton_[i] == 0)
				currentMouseButton_[i] = 2; // Set button to triggered			
			else
				currentMouseButton_[i] = 1; // Set button to pressed

		}


		previousMouseButton_[i] = currentMouseButton_[i];
	}
}


bool InputManager::KeyIsPressed(unsigned char key)
{
	return (currentKey_[key] >= 1);
}


bool InputManager::KeyIsTriggered(unsigned  char key)
{
	return (currentKey_[key] == 2);
}


bool InputManager::KeyPrevIsPressed(unsigned  char key)
{
	return (previousKey_[key] >= 1);
}


bool InputManager::KeyPrevIsTriggered(unsigned  char key)
{
	return (previousKey_[key] == 2);
}


bool InputManager::MouseIsPressed(unsigned  int button)
{
	return (currentMouseButton_[button] >= 1);
}


bool InputManager::MouseIsTriggered(unsigned int button)
{
	return (currentMouseButton_[button] == 2);
}


bool InputManager::MousePrevIsPressed(unsigned int button)
{
	return (previousMouseButton_[button] >= 1);
}


bool InputManager::MousePrevIsTriggered(unsigned int button)
{
	return (previousMouseButton_[button] == 2);
}

glm::vec2 InputManager::getMousePosition()
{
	return mousePos_;
}

