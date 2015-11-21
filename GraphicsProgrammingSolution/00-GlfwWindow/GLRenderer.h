#pragma once
#include <GL\gl_core_4_5.h>
#include <OGLC\GLProgram.h>
#include <vector>
// 1000


struct Renderable
{
public:
	Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices,
		GLint drawMode = GL_TRIANGLES) : 
		program(program), vertexBuffer(vertexBuffer), 
		indexBuffer(indexBuffer),vertexArrayObject(vertexArrayObject), numberOfIndices(numberOfIndices), drawMode(drawMode)
	{

	}
	GLuint GetDrawMode() const noexcept
	{
		return drawMode;
	}
	GLuint GetVertexBuffer()const noexcept
	{
		return vertexBuffer;
	}

	GLuint GetIndexBuffer()const noexcept
	{
		return indexBuffer;
	}

	GLuint GetVertexArrayObject()const noexcept
	{
		return vertexArrayObject;
	}

	GLuint GetIndicesCount() const noexcept
	{
		return numberOfIndices;
	}

	void UpdateUniforms()
	{
		program.Update();
	}
	bool visible = true;
private:
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
	GLuint numberOfIndices;
	GLint drawMode;
	GLProgram & program;
};

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
		):vertices(vertices),numberOfVertices(numberOfVertices),
		indices(indices),numberOfIndices(numberOfIndices),sizeOfVertex(sizeOfVertex),
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

class GLRenderer 
{
public:
	static constexpr int NUM_RENDERABLES = 100;
	GLRenderer() noexcept;
	~GLRenderer() noexcept;
	void Render();
	Renderable & AddRenderable(GLProgram & program,const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layout);
private:
	std::vector<Renderable> renderables;
};


