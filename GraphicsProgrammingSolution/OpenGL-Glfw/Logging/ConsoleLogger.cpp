#include "ConsoleLogger.h"
#include <Windows.h>
#include <iostream>
using std::cout;
using std::endl;

ConsoleLogger::ConsoleLogger()
{
}

void ConsoleLogger::Log(LogLevel level,  const char * message)
{
	ConsoleColor color;
	switch (level)
	{
	case LogLevel::Info:
		color = ConsoleColor::Info;
		break;
	case LogLevel::Warning:
		color = ConsoleColor::Warning;
		break;
	case LogLevel::Issue:
		color = ConsoleColor::Issue;
		break;
	case LogLevel::Error:
		color = ConsoleColor::Error;
		break;
	}
	SetConsoleTextAttribute(consoleHandle, color);
	cout << message << endl;
	SetConsoleTextAttribute(consoleHandle, ConsoleColor::Default);
}


ConsoleLogger::~ConsoleLogger()
{
}
