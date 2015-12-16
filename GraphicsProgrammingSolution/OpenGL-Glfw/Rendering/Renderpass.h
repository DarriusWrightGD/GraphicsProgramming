#pragma once 
#include <gl\gl_core_4_5.h>
#include <vec2.hpp>
#include <Rendering\TextureInfo.h>
#include <vector>

class RenderPass
{
public:
	RenderPass(glm::vec2 size, GLuint samplerId, int numberOfColorAttachments = 1) :
		width(size.x), height(size.y)
	{
		Init(samplerId, numberOfColorAttachments);
	}

	void Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);
	}

	TextureInfo GetColorAttachment(int index) const noexcept
	{
		TextureInfo texInfo;
		if (index < colorAttachments.size())
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

		colorAttachments.resize(numberOfColorAttachments);

		for (auto index = 0u; index < colorAttachments.size(); index++)
		{
			colorAttachments[index].type = GL_TEXTURE_2D;
			glGenTextures(1, &colorAttachments[index].id);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, colorAttachments[index].id);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachments[index].id, 0);
		}

		depthAttachment.sampler = samplerId;
		glGenRenderbuffers(1, &depthAttachment.id);
		glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment.id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);



		GLenum  * drawBufs = new GLenum[numberOfColorAttachments];
		for (size_t i = 0; i < numberOfColorAttachments; i++)
		{
			drawBufs[i] = GL_COLOR_ATTACHMENT0 + i;
		}

		glDrawBuffers(1, drawBufs);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		delete [] drawBufs;
	}

	int width;
	int height;
	GLuint frameBufferHandle;
	TextureInfo depthAttachment;
	std::vector<TextureInfo> colorAttachments;
};
