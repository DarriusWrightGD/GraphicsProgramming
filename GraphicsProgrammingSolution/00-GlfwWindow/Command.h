#pragma once

struct InputInfo
{
	int keyCode;
	int scanCode;
	int action;
	int mods;
};

class Command
{
public:
	Command();
	~Command();
	virtual void Execute(InputInfo inputInfo) = 0;
};

