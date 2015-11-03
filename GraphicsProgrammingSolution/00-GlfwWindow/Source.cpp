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




static const GLchar * vertexShader[] = {
	"#version 450 core" 
};

static const GLchar * fragmentShader[] = {
	"#version 450 core"
};
#include "GlfwWindow.h"
int main()
{
	GLWindowInterface * window = new GlfwWindow();
	int executeValue = window->Execute();
	delete window;
	return executeValue;
}