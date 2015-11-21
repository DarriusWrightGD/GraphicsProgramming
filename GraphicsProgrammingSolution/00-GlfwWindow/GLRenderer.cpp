#include "GLRenderer.h"



GLRenderer::GLRenderer() noexcept
{
	renderables.reserve(NUM_RENDERABLES);
}


GLRenderer::~GLRenderer() noexcept
{

	for (auto & renderable : renderables)
	{
		GLuint buffers[] = { renderable.GetVertexBuffer(),renderable.GetIndexBuffer() };
		glDeleteBuffers(2, buffers);
	}
}

void GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 2);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


	//for (auto & renderable  : renderables)
	//{
	//	renderable.UpdateUniforms();
	//	glBindVertexArray(renderable.GetVertexArrayObject());
	//	glBindBuffer(GL_ARRAY_BUFFER, renderable.GetVertexBuffer());
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable.GetIndexBuffer());
	//	glDrawElements(renderable.GetDrawMode(), renderable.GetIndicesCount(), GL_UNSIGNED_INT, 0);
	//}
}

Renderable & GLRenderer::AddRenderable(const GLProgram & program, const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layouts)
{
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject = 0;

	glCreateVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glCreateBuffers(1, &indexBuffer);
	glNamedBufferData(indexBuffer, sizeof(GLuint) * bufferLayout.GetIndexCount(), bufferLayout.GetIndices(), GL_STATIC_DRAW);

	glCreateBuffers(1, &vertexBuffer);
	glNamedBufferData(vertexBuffer, bufferLayout.GetVertexSize() * bufferLayout.GetVertexCount(), bufferLayout.GetVertices(), GL_STATIC_DRAW);

	auto index = 0;
	for (const auto & layout : layouts)
	{
		glVertexArrayAttribBinding(vertexArrayObject, index, 0);
		glVertexArrayAttribFormat(vertexArrayObject, index, layout.numFloats, GL_FLOAT, GL_FALSE, layout.attributeOffset);
		glVertexArrayVertexBuffer(vertexArrayObject, index, vertexBuffer, layout.attributeOffset, bufferLayout.GetVertexSize());
		glEnableVertexArrayAttrib(vertexArrayObject, index);
		index++;
	}

	Renderable renderable(program, vertexArrayObject, vertexBuffer, indexBuffer, bufferLayout.GetIndexCount());
	renderables.push_back(renderable);
	return renderables[renderables.size() - 1];
}
