#pragma once
#include "GLWindowInterface.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include "GlfwInputHandler.h"
using std::string;
class GlfwWindow : public GLWindowInterface
{
public:
	GlfwWindow(int width = 640, int height = 480, const char * title = "GLWindow", int glMajor = 4, int glMinor = 5);
	~GlfwWindow();

	// Inherited via GLWindowInterface
	virtual void Update() override;
	virtual void Render() override;
	virtual int Execute() override;
	virtual void SetTitle(const char * title) override;

protected:
	GLFWwindow * window;
	InputHandler * input;
	string title;
	int width, height, glMajor, glMinor;
	double time;
	int Init();
	void CleanUp();
	
};

