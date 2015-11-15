#pragma once
#include "WindowInterface.h"
#include <GL\gl_core_4_5.h>
#include <GLFW\glfw3.h>
#include <string>
#include <Input\GlfwInputHandler.h>

using std::string;
class GlfwWindow : public WindowInterface
{
public:
	GlfwWindow(int width = 640, int height = 480, const char * title = "GLWindow", int glMajor = 4, int glMinor = 5);
	virtual ~GlfwWindow();

	// Inherited via GLWindowInterface
	virtual void Initialize() = 0;
	virtual int Execute() final;
	virtual void SetTitle(const char * title) final;

protected:
	virtual void SwapBuffers();
	virtual void Shutdown() = 0;
	GLFWwindow * window;
	InputHandler * input;
	string title;
	int width, height, glMajor, glMinor;
	double time;
private:
	static GlfwWindow * instance;
	static void Resize(GLFWwindow * window,int w, int h);
	int InitGLFW();
	void CleanUp();

};

