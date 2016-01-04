#pragma once 
#include <gl\gl_core_4_5.h>
#include <vec2.hpp>
#include <Rendering\TextureInfo.h>
#include <Util\ServiceLocator.h>
#include <Logging\Logger.h>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

class RenderPass
{
public:
	RenderPass(glm::vec2 size, GLuint samplerId, int numberOfColorAttachments = 1) :
		width(static_cast<int>(size.x)), height(static_cast<int>(size.y))
	{
		Init(samplerId, numberOfColorAttachments);
	}

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
	}

	GLuint & GetFrameBuffer() noexcept
	{
		return frameBufferHandle;
	}

	TextureInfo GetColorAttachment(int index) const noexcept
	{
		TextureInfo texInfo;
		if (static_cast<size_t>(index) < colorAttachments.size())
		{
			return colorAttachments[index];
		}
		texInfo.id = -1;
		return texInfo;
	}

	TextureInfo GetDepthTexture() const noexcept
	{
		return depthAttachment;
	}

	int & GetWidth() noexcept
	{
		return width;
	}

	int & GetHeight() noexcept
	{
		return height;
	}

private:

	void Init(GLuint samplerId, int numberOfColorAttachments)
	{
		glGenFramebuffers(1, &frameBufferHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);

		for (auto i = 0u; i < numberOfColorAttachments; i++)
		{

			TextureInfo colorTexture;

			glGenTextures(1, &colorTexture.id);
			colorTexture.sampler = samplerId;
			colorTexture.type = GL_TEXTURE_2D;
			glBindTexture(GL_TEXTURE_2D, colorTexture.id);
			glTexStorage2D(GL_TEXTURE_2D, 9, GL_RGBA8, width, height);
			colorAttachments.push_back(colorTexture);

		}

		glGenTextures(1, &depthAttachment.id);
		glBindTexture(GL_TEXTURE_2D, depthAttachment.id);
		glTexStorage2D(GL_TEXTURE_2D, 9, GL_DEPTH_COMPONENT32F, width, height);
		depthAttachment.type = GL_TEXTURE_2D;
		depthAttachment.sampler = samplerId;


		GLenum * drawBuffers = new GLenum[colorAttachments.size()];
		for (auto i = 0u; i < colorAttachments.size(); i++)
		{
			auto colorAttachment = GL_COLOR_ATTACHMENT0 + i;
			glFramebufferTexture(GL_FRAMEBUFFER, colorAttachment, colorAttachments[i].id, 0);
			drawBuffers[i] = colorAttachment;
		}


		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthAttachment.id, 0);


		glDrawBuffers(numberOfColorAttachments, drawBuffers);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			Services.Get<Logger>()->Log(LogLevel::Error, "Framebuffer is not complete");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Bind4(GLuint samplerId, int numberOfColorAttachments)
	{
		
	}

	int width;
	int height;
	GLuint frameBufferHandle;
	TextureInfo depthAttachment;
	std::vector<TextureInfo> colorAttachments;
};
