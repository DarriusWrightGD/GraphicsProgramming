#pragma once
#include "InputHandler.h"
#include "InputInfo.h"
#include <GLFW\glfw3.h>
class GlfwInputHandler : public InputHandler
{
public:
	GlfwInputHandler();
	~GlfwInputHandler();
	static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (inputInstance)
		{
			inputInstance->handleKeys({ key, scancode, action, mods });
		}
	}
	// Inherited via InputHandler
	virtual void handleKeys(InputInfo input) override;
};

