#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Windows.h>
#include <string>

#include "MathUtils.h"
#include "ISystem.h"

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1


class InputManager : public ISystem
{
public:

	static InputManager* getInstance()
	{
		if (!instance_)		
			instance_ = new InputManager();
		
		return instance_;
	}

	void Initialize();
	void Update(float dt = 0);
	void Shutdown() {};

	bool HandleInputMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	

	/*  Keyboard input */
	bool KeyIsPressed(unsigned  char key);
	bool KeyIsTriggered(unsigned  char key);
	bool KeyPrevIsPressed(unsigned  char key);
	bool KeyPrevIsTriggered(unsigned  char key);

	/*  Mouse input */
	bool MouseIsPressed(unsigned  int button);
	bool MouseIsTriggered(unsigned  int button);
	bool MousePrevIsPressed(unsigned  int button);
	bool MousePrevIsTriggered(unsigned  int button);

	glm::vec2 getMousePosition();


private:
	InputManager() {}

	static InputManager* instance_;

	char	currentKey_[256]{};
	char	previousKey_[256]{};

	char	currentMouseButton_[2]{};
	char	previousMouseButton_[2]{};

	glm::vec2	mousePos_;
	bool	isMouseWithinWindow_ = true;


};

#endif