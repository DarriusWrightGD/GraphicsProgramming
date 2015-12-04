#include "BufferDemo.h"

#include <vec4.hpp>
using glm::vec4;
vec4 vertices[] = {
	vec4(-0.5f,-0.5f,0.0f,1.0f),
	vec4(0.0f,0.5f,0.0f,1.0f),
	vec4(0.5f,-0.5f,0.0f,1.0f),
};

vec4 colors[] = {
	vec4(0.3f,0.3f,0.7f,1.0f),
	vec4(0.8f,0.9f,0.1f,1.0f),
	vec4(0.9f,0.2f,1.0f,1.0f),
};

BufferDemo::BufferDemo()
{
}


BufferDemo::~BufferDemo()
{
}

void BufferDemo::Update()
{
}

void BufferDemo::Render()
{
	glClearColor(0, 0, 0, 1);
	program.Use();
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void BufferDemo::Initialize()
{
	SetTitle("BufferDemo");
	program.Initialize();
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/buffer.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/buffer.frag");
	program.Build();
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glCreateBuffers(1, &positionBuffer);
	glCreateBuffers(1, &positionBuffer);
	glCreateBuffers(1, &colorBuffer);


	glNamedBufferStorage(positionBuffer, sizeof(vec4) * 3, nullptr, GL_MAP_WRITE_BIT);
	glNamedBufferStorage(positionBuffer2, sizeof(vec4) * 3, nullptr, GL_MAP_WRITE_BIT);
	glNamedBufferStorage(colorBuffer, sizeof(vec4) * 3, nullptr, GL_MAP_WRITE_BIT);
	//glNamedBufferSubData(positionBuffer, 0, sizeof(vec4) * 3, vertices);

	//glNamedBufferStorage(positionBuffer, sizeof(vec4) * 3, vertices, GL_MAP_WRITE_BIT);

	//auto positionMemory = glMapNamedBuffer(positionBuffer, GL_WRITE_ONLY);
	//memcpy(positionMemory, vertices, sizeof(vec4) * 3);
	//glUnmapNamedBuffer(positionBuffer);

	//Prefer this mapping mechanism as it has a stricter contract
	auto positionMemory = glMapNamedBufferRange(positionBuffer, 0, sizeof(vec4) * 3, GL_MAP_WRITE_BIT);
	memcpy(positionMemory, vertices, sizeof(vec4) * 3);
	glUnmapNamedBuffer(positionBuffer);

	auto colorMemory = glMapNamedBufferRange(colorBuffer, 0, sizeof(vec4) * 3, GL_MAP_WRITE_BIT);
	memcpy(colorMemory, colors, sizeof(vec4) * 3);
	glUnmapNamedBuffer(colorBuffer);

	//If you need to clear a buffer with constant data then an efficent way to do so is the following glClearNamedBufferSubData
	//glClearNamedBufferSubData(positionBuffer,GL_RGBA,0,sizeof(vec4) * 3,)

	//To copy do the following
	//glCopyNamedBufferSubData(positionBuffer, positionBuffer2,0,0,sizeof(vec4) * 3);
	//glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glVertexArrayVertexBuffer(vertexArray, 0, positionBuffer, 0, sizeof(vec4));
	glVertexArrayVertexBuffer(vertexArray, 1, colorBuffer, 0, sizeof(vec4));
	glVertexArrayAttribFormat(vertexArray, 0, 4, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(vertexArray, 1, 4, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(vertexArray, 0);
	glEnableVertexArrayAttrib(vertexArray, 1);

}

void BufferDemo::Shutdown()
{
	program.Delete();
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteBuffers(1, &positionBuffer);
	glDeleteBuffers(1, &colorBuffer);
	glDeleteBuffers(1, &positionBuffer2);
}

void BufferDemo::OnResize(int width, int height)
{
}
