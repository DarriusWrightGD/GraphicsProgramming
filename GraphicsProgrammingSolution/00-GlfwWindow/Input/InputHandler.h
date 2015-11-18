#pragma once
#include "InputInfo.h"
#include <functional>
#include <unordered_map>
#include <vector>
using std::function;
using std::unordered_map;
using std::vector;

class InputHandler
{
public:
	InputHandler() noexcept;
	~InputHandler()noexcept;
	void addBinding(int keyCode, function<void(InputInfo)> callback) noexcept;
	virtual void handleKeys(InputInfo input) = 0;
protected:
	static InputHandler * inputInstance;
	unordered_map<int, vector<function<void(InputInfo)>>> keyBindings;
};

