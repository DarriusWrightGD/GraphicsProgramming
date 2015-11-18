#include "GLRenderer.h"



GLRenderer::GLRenderer() noexcept
{
	renderables.reserve(NUM_RENDERABLES);
}


GLRenderer::~GLRenderer() noexcept
{
}

void GLRenderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto & renderable  : renderables)
	{
		renderable.UpdateUniforms();
		glBindBuffer(GL_ARRAY_BUFFER, renderable.GetVertexBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable.GetIndexBuffer());
		glDrawElements(renderable.GetDrawMode(), renderable.GetIndicesCount(), GL_UNSIGNED_INT, 0);
	}
}

Renderable & GLRenderer::AddRenderable(const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layouts)
{
	GLuint vertexBuffers[2];
	GLuint vertexArrayObject;

	glCreateVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glCreateBuffers(2, vertexBuffers);
	glNamedBufferData(vertexBuffers[0], bufferLayout.sizeOfVertex * bufferLayout.numberOfVertices, bufferLayout.vertices, GL_STATIC_DRAW);
	glNamedBufferData(vertexBuffers[1], sizeof(GLuint) * bufferLayout.numberOfIndices, bufferLayout.indices,GL_STATIC_DRAW);

	auto index = 0;
	for (const auto & layout : layouts)
	{
	    glVertexArrayAttribBinding(vertexArrayObject, index, 0);
		glVertexArrayAttribFormat(vertexArrayObject, index, layout.numFloats, GL_FLOAT, GL_FALSE, layout.attributeOffset);
		glVertexArrayVertexBuffer(vertexArrayObject, index, vertexBuffers[0], layout.vertexElementOffset, bufferLayout.sizeOfVertex);
		glEnableVertexArrayAttrib(vertexArrayObject, index);
		index++;
	}

	Renderable renderable(vertexArrayObject, vertexBuffers[0],vertexBuffers[1], bufferLayout.numberOfIndices);
	renderables.push_back(renderable);
	return renderables[renderables.size() - 1];
}
