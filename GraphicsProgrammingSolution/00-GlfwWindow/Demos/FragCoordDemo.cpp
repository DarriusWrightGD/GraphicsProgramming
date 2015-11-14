#include "FragCoordDemo.h"



FragCoordDemo::FragCoordDemo()
{
}


FragCoordDemo::~FragCoordDemo()
{
}

void FragCoordDemo::Update()
{
}

void FragCoordDemo::Render()
{
	GLfloat color[] = { 0,0,0,1 };
	glClearBufferfv(GL_COLOR, 0, color);
	program.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void FragCoordDemo::Initialize()
{
	program.Initialize();
	program.AddShaderFile(Vertex, "Assets/Shaders/Vertex/fragCoord.vert");
	program.AddShaderFile(Fragment,"Assets/Shaders/Fragment/fragCoord.frag");
	program.Build();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
}

void FragCoordDemo::Shutdown()
{
	program.Delete();
	glDeleteVertexArrays(1,&vertexArray);
}

void FragCoordDemo::OnResize(int width, int height)
{
}
