#include "VertexBufferDemo.h"

#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{

	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	if (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d: %s\n",
			file, line, glewGetErrorString(glErr));
		retCode = 1;
	}
	return retCode;
}

VertexBufferDemo::VertexBufferDemo()
{
}


VertexBufferDemo::~VertexBufferDemo()
{
}

void VertexBufferDemo::Update()
{
}

void VertexBufferDemo::Render()
{
	glClearColor(0, 0, 0, 1);
	program.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

ColorVertex vertices[] = {
	{ vec4(-.5f,-.5,0.0f,1.0f),{ 1.0f,.6f,.5,1.0 } },
{vec4(0.0f,.5,0.0f,1.0f),{ 1.0f,.6f,.5,1.0 }},
{vec4(.5f,-.5,0.0f,1.0f), {1.0f,.6f,.5,1.0}}
};

void VertexBufferDemo::Initialize()
{
	SetTitle("VertexBufferDemo");
	
	program.Initialize();
	program.AddShaderFile(Vertex, "Assets/Shaders/Vertex/buffer.vert");
	program.AddShaderFile(Fragment, "Assets/Shaders/Fragment/buffer.frag");
	program.Build();

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glCreateBuffers(1, &vertexBuffer);

	glNamedBufferData(vertexBuffer, sizeof(ColorVertex) * 3, vertices, GL_STATIC_DRAW);

	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4));

	glVertexArrayVertexBuffer(vao, 0, vertexBuffer, 0, sizeof(ColorVertex));
	glVertexArrayVertexBuffer(vao, 1, vertexBuffer, sizeof(vec4), sizeof(ColorVertex));

	glEnableVertexArrayAttrib(vao, 0);
	glEnableVertexArrayAttrib(vao, 1);

}

void VertexBufferDemo::Shutdown()
{
	program.Delete();
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vertexBuffer);
}

void VertexBufferDemo::OnResize(int width, int height)
{
}
