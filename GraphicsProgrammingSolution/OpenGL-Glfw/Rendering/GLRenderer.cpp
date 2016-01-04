#include "GLRenderer.h"
#include <Rendering\Renderable.h>
#include <Rendering\GuiRenderable.h>
#include <Exceptions\FileNotFoundException.h>
#include <Rendering\RenderUtil.h>
#include <SOIL.h>

GLRenderer::GLRenderer() noexcept
{
	renderables.reserve(NUM_RENDERABLES);
	guiRenderables.reserve(NUM_RENDERABLES);
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
	RenderObjects();
	RenderUi();
}

void GLRenderer::RenderObjects()
{
	for (auto & renderable : renderables)
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

void GLRenderer::RenderUi()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto & guiRenderable : guiRenderables)
	{
		if (guiRenderable.visible)
		{
			guiRenderable.Update();
			glDrawArrays(GL_TRIANGLES, 0, 6);
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

Renderable * GLRenderer::AddRenderable(GLProgram & program, const VertexBufferLayout & bufferLayout, const std::vector<VertexLayout> & layouts, const std::vector<UniformUpdate> & instanceUniforms, GLint drawMode, DrawFunction function)
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

	Renderable renderable(program, vertexArrayObject, vertexBuffer, indexBuffer, bufferLayout.GetIndexCount(), instanceUniforms, drawMode, function);
	renderables.push_back(renderable);
	return &renderables[renderables.size() - 1];
}

GuiRenderable * GLRenderer::AddGuiRenderable(GLProgram & program, const std::vector<UniformUpdate>& instanceUniforms)
{
	GuiRenderable guiRenderable(program, instanceUniforms);
	guiRenderables.push_back(guiRenderable);
	return &guiRenderables[guiRenderables.size()-1];
}

RenderPass * GLRenderer::AddRenderPass(glm::vec2 size, SamplerType samplerType, int numberOfColorAttachments)
{
	RenderPass * pass = new RenderPass(size, this->GetSampler(samplerType).sampler, numberOfColorAttachments);
	renderPasses.push_back(pass);
	return pass;
}

TextureInfo GLRenderer::CreateTexture(GLuint textureIndex, const char * filePath, SamplerType sampler)
{
	auto width = 0, height = 0, channels = 0;
	auto imageBytes = SOIL_load_image(filePath, &width, &height, &channels, SOIL_LOAD_AUTO);

	if (imageBytes != nullptr)
	{
		RenderUtil::FlipY(imageBytes, width, height, channels);
		GLuint textureId;

		int colorComponents = GL_RGBA8;
		int colorChannels = GL_RGBA;

		switch (channels)
		{
		case 1:
			colorComponents = GL_R8;
			colorChannels = GL_RED;
			break;
		case 2:
			colorComponents = GL_RG8;
			colorChannels = GL_RG;
			break;
		case 3:
			colorComponents = GL_RGB8;
			colorChannels = GL_RGB;
			break;
		case 4:
			colorComponents = GL_RGBA8;
			colorChannels = GL_RGBA;
			break;
		}

		glActiveTexture(GL_TEXTURE0 + textureIndex);
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexStorage2D(GL_TEXTURE_2D, 1, colorComponents, width, height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, colorChannels, GL_UNSIGNED_BYTE, imageBytes);
		return{ textureId ,GL_TEXTURE_2D, GetSampler(sampler).sampler };
	}
	else
	{
		throw FileNotFoundException(filePath);
	}
}
