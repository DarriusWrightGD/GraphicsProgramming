#pragma once
#include <memory>
#include <string>
enum class LogLevel
{
	Info,
	Warning,
	Issue,
	Error
};
class Logger
{
public:
	virtual void Log(LogLevel level, const char * message) = 0;
	Logger();
	~Logger();
protected:

};

