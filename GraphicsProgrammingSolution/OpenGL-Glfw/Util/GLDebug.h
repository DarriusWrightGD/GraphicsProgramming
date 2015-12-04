#pragma once
#include <Windows.h>
#include <iostream>
#include <GL\gl_core_4_5.h>
#include <Util\ServiceLocator.h>
#include <Logging\Logger.h>
using std::cout;
using std::endl;


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void APIENTRY debugCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam) {
	auto logger = Services.Get<Logger>();
	if (logger != nullptr)
	{
		std::string logMessage;
		LogLevel level;
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			level = LogLevel::Info;
			logMessage += "NOTIFCATION";
			break;
		case GL_DEBUG_SEVERITY_LOW:
			level = LogLevel::Warning;
			logMessage += "LOW";
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			level = LogLevel::Issue;
			logMessage += "MEDIUM";
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			level = LogLevel::Error;
			logMessage += "HIGH";
			break;
		}
		logMessage += " : ";
		logMessage += message;
		logMessage += "(";
		switch (type) {
		case GL_DEBUG_TYPE_ERROR:
			logMessage += "ERROR";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			logMessage += "DEPRECATED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			logMessage += "UNDEFINED_BEHAVIOR";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			logMessage += "PORTABILITY";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			logMessage += "PERFORMANCE";
			break;
		case GL_DEBUG_TYPE_OTHER:
			logMessage += "OTHER";
			break;
		}
		logMessage += ")\n";
		logger->Log(level, logMessage.c_str());
	}
}