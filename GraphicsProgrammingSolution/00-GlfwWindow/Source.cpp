#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::unordered_map;
using std::function;
using std::vector;


void errorCallback(int error, const char * description)
{
	fputs(description, stderr);
}

class KeyHandler
{
public:
	KeyHandler()
	{
		keyHandlerInstance = this;
	}

	void addBinding(int keyCode, function<void(GLFWwindow*,int)> callback)
	{
		auto keyBindingIter = keyBindings.find(keyCode);
		if (keyBindingIter == keyBindings.end())
		{
			vector<function<void(GLFWwindow*,int)>> functions;
			functions.push_back(callback);
			keyBindings.insert({ keyCode, functions });
		}
		else
		{
			keyBindingIter->second.push_back(callback);
		}
	}

	static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (keyHandlerInstance)
		{
			keyHandlerInstance->handleKeys(window, key, scancode, action, mods);
		}
	}

private:
	static KeyHandler * keyHandlerInstance;
	void handleKeys(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		auto keyBindingIter = keyBindings.find(key);
		if (keyBindingIter != keyBindings.end())
		{
			for (auto callback : keyBindingIter->second)
			{
				callback(window, action);
			}
		}
	}
	unordered_map<int, vector<function<void(GLFWwindow*,int)>>> keyBindings;
};

KeyHandler * KeyHandler::keyHandlerInstance;

int main()
{
	glfwSetErrorCallback(errorCallback);
	GLFWwindow * window;
	KeyHandler keyHandler;
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "Hello Glfw", NULL, NULL);
	glfwSetKeyCallback(window, KeyHandler::keyCallback);
	keyHandler.addBinding(GLFW_KEY_ESCAPE, [](GLFWwindow * window, int action) 
	{
		if (action == GLFW_PRESS)
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
	const GLubyte * renderer = glGetString(GL_RENDERER);
	const GLubyte * version = glGetString(GL_VERSION);

	printf("Renderer : %s\n", renderer);
	printf("Version : %s\n", version);

	int w, h;
	glfwGetFramebufferSize(window, &w, &h);
	glViewport(0, 0, w, h);
	static const GLfloat color[] = { 0.6f,0.3f,0.3f,1.0f };
	while (!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, color);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}