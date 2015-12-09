#pragma once
#include <GL\gl_core_4_5.h>
// 1000


struct VertexLayout
{
	int numFloats;
	int attributeOffset;
};

struct VertexBufferLayout
{
	VertexBufferLayout(
		void * vertices,
		GLuint numberOfVertices,
		unsigned int * indices,
		GLuint numberOfIndices,
		GLint sizeOfVertex,
		GLint drawMode = GL_TRIANGLES
		) :vertices(vertices), numberOfVertices(numberOfVertices),
		indices(indices), numberOfIndices(numberOfIndices), sizeOfVertex(sizeOfVertex),
		drawMode(drawMode)
	{

	}

	void * GetVertices() const noexcept
	{
		return vertices;
	}

	GLuint GetVertexCount()const noexcept
	{
		return numberOfVertices;
	}

	unsigned int * GetIndices() const noexcept
	{
		return indices;
	}

	GLuint GetIndexCount()const noexcept
	{
		return numberOfIndices;
	}

	GLuint GetVertexSize()const noexcept
	{
		return sizeOfVertex;
	}

	GLint GetDrawMode()const noexcept
	{
		return drawMode;
	}

private:
	void * vertices;
	GLuint numberOfVertices;
	unsigned int * indices;
	GLuint numberOfIndices;
	GLint sizeOfVertex;
	GLint drawMode;
};
