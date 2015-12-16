#include "GLRenderer.h"
#include <Rendering\Renderable.h>



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

	for (auto pass : renderPasses)
	{
		delete pass;
		pass = nullptr;
	}
}

void GLRenderer::Render()
{
	for (auto & renderable  : renderables)
	{
		if (renderable.visible)
		{
		
			renderable.Update();
			glBindVertexArray(renderable.GetVertexArrayObject());
			glBindBuffer(GL_ARRAY_BUFFER, renderable.GetVertexBuffer());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable.GetIndexBuffer());
			glDrawElements(renderable.GetDrawMode(), renderable.GetIndicesCount(), GL_UNSIGNED_INT, 0);
		}
		
	}
}

GLSampler GLRenderer::GetSampler(SamplerType samplerType)
{
	if (!samplersInitialized)
	{
		InitializeSamplers();
	}
	
	return samplerMap[samplerType];
}

void GLRenderer::InitializeSamplers()
{
	GLuint samplers[4];
	glGenSamplers(4, samplers);
	samplerMap.insert({ SamplerType::Linear,{ samplers[0] } });
	samplerMap.insert({ SamplerType::Cubemap,{ samplers[1] } });
	samplerMap.insert({ SamplerType::Nearest,{ samplers[2] } });
	samplerMap.insert({ SamplerType::Projection,{ samplers[3] } });

	glSamplerParameteri(samplers[0], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(samplers[0], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(samplers[0], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(samplers[0], GL_TEXTURE_WRAP_T, GL_REPEAT);


	glSamplerParameteri(samplers[1], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(samplers[1], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(samplers[1], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(samplers[1], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(samplers[1], GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	glSamplerParameteri(samplers[2], GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(samplers[2], GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(samplers[2], GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(samplers[2], GL_TEXTURE_WRAP_T, GL_REPEAT);


	glSamplerParameteri(samplers[3], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(samplers[3], GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(samplers[3], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glSamplerParameteri(samplers[3], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

}

void GLRenderer::Render(Renderable * renderable)
{
	if (renderable->visible)
	{
		renderable->Update();
		glBindVertexArray(renderable->GetVertexArrayObject());
		glBindBuffer(GL_ARRAY_BUFFER, renderable->GetVertexBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable->GetIndexBuffer());
		glDrawElements(renderable->GetDrawMode(), renderable->GetIndicesCount(), GL_UNSIGNED_INT, 0);
	}
}

Renderable * GLRenderer::AddRenderable(GLProgram & program, const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layouts, const std::vector<UniformUpdate> & instanceUniforms)
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

	Renderable renderable(program, vertexArrayObject, vertexBuffer, indexBuffer, bufferLayout.GetIndexCount(),instanceUniforms);
	renderables.push_back(renderable);
	return &renderables[renderables.size() - 1];
}

RenderPass * GLRenderer::AddRenderPass(glm::vec2 size, SamplerType samplerType, int numberOfColorAttachments)
{
	RenderPass * pass = new RenderPass(size, this->GetSampler(samplerType).sampler, numberOfColorAttachments);
	renderPasses.push_back(pass);
	return pass;
}
