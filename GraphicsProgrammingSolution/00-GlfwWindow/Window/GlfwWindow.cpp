#include "GlfwWindow.h"
#include <iostream>

void errorCallback(int error, const char * description)
{
	fputs(description, stderr);
}

GlfwWindow * GlfwWindow::instance;

GlfwWindow::GlfwWindow(int width, int height, const char * title, int glMajor, int glMinor):
	width(width), height(height), title(title), glMajor(glMajor), glMinor(glMinor)
{
	instance = this;
}


GlfwWindow::~GlfwWindow()
{
}

int GlfwWindow::Execute()
{
	auto initReturn = InitGLFW();
	if (initReturn != 0)
	{
		return initReturn;
	}
	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	width = w;
	height = h;
	OnResize(w, h);
	Initialize();

	while (!glfwWindowShouldClose(window))
	{
		time = glfwGetTime();

		Render();
		SwapBuffers();
		Update();
		glfwPollEvents();
	}

	CleanUp();

	return 0;
}

void GlfwWindow::CleanUp()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	delete input;
	Shutdown();
}

void GlfwWindow::SetTitle(const char * title)
{
	this->title = title;
	glfwSetWindowTitle(window, title);
}

void GlfwWindow::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void GlfwWindow::Resize(GLFWwindow * window, int w, int h)
{
	if (instance)
	{
		instance->width = w;
		instance->height = h;
		instance->OnResize(w, h);
	}
}

int GlfwWindow::InitGLFW()
{
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit())
	{
		return -1;
	}


	//glfwWindowHint(GLFW_DEPTH_BITS, 24);
	window = glfwCreateWindow(640, 480, title.c_str(),NULL, NULL);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 32);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwSetKeyCallback(window, GlfwInputHandler::keyCallback);
	glfwSetWindowSizeCallback(window, GlfwWindow::Resize);
	input = new GlfwInputHandler();
	input->addBinding(GLFW_KEY_ESCAPE, [this](InputInfo info)
	{
		if (info.action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	});
	
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "Glew failed" << std::endl;
		return -1;
	}

	return 0;
}
