#include "GlfwInputHandler.h"



GlfwInputHandler::GlfwInputHandler()
{
}


GlfwInputHandler::~GlfwInputHandler()
{
}

void GlfwInputHandler::handleKeys(InputInfo input) noexcept
{
	auto keyBindingIter = keyBindings.find(input.keyCode);
	if (keyBindingIter != keyBindings.end())
	{
		for (auto callback : keyBindingIter->second)
		{
			callback(input);
		}
	}
}
