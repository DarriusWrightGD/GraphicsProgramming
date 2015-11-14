#include "ShaderDemo.h"

static const GLchar * vertexShaderSource = {
	"#version 440\n"
	"void main(){\n"
	"const vec4 vertices[3] = vec4[3]\n"
	"(vec4(0.25,-0.25,0.5,1.0),\n"
	"vec4(-0.25,-0.25,0.5,1.0),\n"
	"vec4(0.25,0.25,0.5,1.0));\n"
	"gl_Position = vertices[gl_VertexID];\n"
	"}\n"
};

static const GLchar * fragmentShaderSource = {
	"#version 440\n"
	"out vec4 color;\n"
	"void main(){\n"
	"color = vec4(0.2,0.8,1.0,1.0);\n"
	"}\n"
};

ShaderDemo::ShaderDemo()
{
}

ShaderDemo::~ShaderDemo()
{
}


void ShaderDemo::BuildProgram()
{
	glProgram.Initialize();
	glProgram.AddShaderFile(Vertex, "Assets/Shaders/Vertex/triangleShader.vert");
	glProgram.AddShaderFile(Fragment, "Assets/Shaders/Fragment/triangleShader.frag");
	glProgram.Build();
}

void ShaderDemo::Initialize()
{
	SetTitle("ShaderDemo");
	BuildProgram();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glPointSize(40.0f);
}

void ShaderDemo::Shutdown()
{
	glDeleteVertexArrays(1, &vertexArray);
	glProgram.Delete();
}

void ShaderDemo::OnResize(int width, int height)
{
}

void ShaderDemo::Update()
{
}

void ShaderDemo::Render()
{
	const GLfloat color[] = { static_cast<GLfloat>(cos(time)) * 0.6f,static_cast<GLfloat>(sin(time)) * 0.3f,0.3f,1.0f };
	glClearBufferfv(GL_COLOR, 0, color);
	glBindVertexArray(vertexArray);
	glProgram.Use();
	//glDrawArrays(GL_POINTS, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
