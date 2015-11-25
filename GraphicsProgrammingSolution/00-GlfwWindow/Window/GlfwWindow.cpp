#include "GlfwWindow.h"
#include <iostream>
#include <Util\ServiceLocator.h>
#include <Rendering\GLRenderer.h>
#include <Util\GLDebug.h>
#include <Logging\ConsoleLogger.h>
#include <Cameras\Camera.h>

using std::cout;
using std::endl;


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
	Initialize();
	OnResize(w, h);

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
	Shutdown();
	Services.CleanUp();
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
	if (instance && w != 0 && h !=0)
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	window = glfwCreateWindow(640, 480, title.c_str(),NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, GlfwInputHandler::keyCallback);
	glfwSetWindowSizeCallback(window, GlfwWindow::Resize);
	Services.Set<InputHandler, GlfwInputHandler>();

	input = Services.Get<InputHandler>();
	input->addBinding(GLFW_KEY_ESCAPE, [this](InputInfo info)
	{
		if (info.action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	});
	


	glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		std::cout << "Glew failed" << std::endl;
		return -1;
	}

#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(debugCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,0,nullptr,GL_TRUE);
#endif
	

	Services.Set<GLRenderer, GLRenderer>();
	Services.Set<Logger, ConsoleLogger>();
	Services.Set<Camera, Camera>(new Camera(static_cast<float>(width)/height));
	camera = Services.Get<Camera>();

	return 0;
}
