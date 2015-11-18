#include "InputHandler.h"

InputHandler * InputHandler::inputInstance;

InputHandler::InputHandler() noexcept
{
	inputInstance = this;
}

InputHandler::~InputHandler() noexcept
{
}

void InputHandler::addBinding(int keyCode, function<void(InputInfo)> callback) noexcept
{
	auto keyBindingIter = keyBindings.find(keyCode);
	if (keyBindingIter == keyBindings.end())
	{
		vector<function<void(InputInfo)>> functions;
		functions.push_back(callback);
		keyBindings.insert({ keyCode, functions });
	}
	else
	{
		keyBindingIter->second.push_back(callback);
	}
}

