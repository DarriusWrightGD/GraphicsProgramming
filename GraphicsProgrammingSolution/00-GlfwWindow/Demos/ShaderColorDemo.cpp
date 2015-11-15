#include "ShaderColorDemo.h"



ShaderColorDemo::ShaderColorDemo()
{
}


ShaderColorDemo::~ShaderColorDemo()
{
}

void ShaderColorDemo::Update()
{
}

void ShaderColorDemo::Render()
{
	glClearColor(0, 0, 0, 1);
	program.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ShaderColorDemo::Initialize()
{
	SetTitle("ShaderColorDemo");
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/shaderColor.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/shaderColor.frag");
	program.Build();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
}

void ShaderColorDemo::Shutdown()
{
	program.Delete();
	glDeleteVertexArrays(1, &vertexArray);
}

void ShaderColorDemo::OnResize(int width, int height)
{
}
