#include "GlfwWindow.h"

void errorCallback(int error, const char * description)
{
	fputs(description, stderr);
}

GlfwWindow::GlfwWindow(int width, int height, const char * title, int glMajor, int glMinor):
	width(width), height(height), title(title), glMajor(glMajor), glMinor(glMinor)
{
	
}


GlfwWindow::~GlfwWindow()
{
}

void GlfwWindow::Update()
{
	glfwPollEvents();
}

void GlfwWindow::Render()
{
	const GLfloat color[] = { static_cast<GLfloat>(cos(time)) * 0.6f,static_cast<GLfloat>(sin(time)) * 0.3f,0.3f,1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glfwSwapBuffers(window);
}

int GlfwWindow::Execute()
{
	auto initReturn = Init();
	
	if (initReturn != 0)
	{
		return initReturn;
	}

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	while (!glfwWindowShouldClose(window))
	{
		time = glfwGetTime();
		Render();
		Update();
	}

	CleanUp();

	return 0;
}

void GlfwWindow::CleanUp()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	delete input;
}

void GlfwWindow::SetTitle(const char * title)
{
	this->title = title;

}

int GlfwWindow::Init()
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
	window = glfwCreateWindow(640, 480, title.c_str(), NULL, NULL);
	glfwSetKeyCallback(window, GlfwInputHandler::keyCallback);
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
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	return 0;
}
