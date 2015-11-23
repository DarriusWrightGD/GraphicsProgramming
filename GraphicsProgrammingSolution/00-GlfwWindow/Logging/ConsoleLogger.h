#pragma once
#include <Logging\Logger.h>
#include <Windows.h>
enum ConsoleColor
{
	Default = 1,
	Info = 15,
	Warning = 14,
	Issue = 13,
	Error = 12
};

class ConsoleLogger : public Logger
{
public:
	~ConsoleLogger();
	ConsoleLogger();
	virtual void Log(LogLevel level, const char * message) override;
private:
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

};

