#pragma once
#include <GL\gl_core_4_5.h>
#include <OGLC\GLProgram.h>
#include <vector>



struct Renderable
{
public:
	Renderable(GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices,
		GLint drawMode = GL_TRIANGLES) : 
		vertexBuffer(vertexBuffer), indexBuffer(indexBuffer),vertexArrayObject(vertexArrayObject), numberOfIndices(numberOfIndices)
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
private:
	bool visible = true;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
	GLuint numberOfIndices;
	GLint drawMode;
	GLProgram program;
};

struct VertexLayout
{
	int numFloats;
	int attributeOffset;
	int vertexElementOffset;
};

struct VertexBufferLayout
{
	void * vertices;
	GLuint numberOfVertices;
	unsigned int * indices;
	GLuint numberOfIndices;
	GLint sizeOfVertex;
	GLint drawMode = GL_TRIANGLES;
};

class GLRenderer 
{
public:
	static constexpr int NUM_RENDERABLES = 100;
	GLRenderer() noexcept;
	~GLRenderer() noexcept;
	void Render();
	Renderable & AddRenderable(const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layout);
private:
	std::vector<Renderable> renderables;
};


