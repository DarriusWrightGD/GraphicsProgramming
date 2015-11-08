#include "BufferDemo.h"



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
}

#include <vec4.hpp>
using glm::vec4;
vec4 vertices[] = {
	vec4()
};

void BufferDemo::Initialize()
{
	program.Initialize();
	program.AddShaderFile(Vertex, "");
	program.AddShaderFile(Fragment, "");

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	glCreateBuffers(1, &positionBuffer);
	glNamedBufferStorage(positionBuffer,sizeof(vec4) * 3,)
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);

}

void BufferDemo::Shutdown()
{
}
