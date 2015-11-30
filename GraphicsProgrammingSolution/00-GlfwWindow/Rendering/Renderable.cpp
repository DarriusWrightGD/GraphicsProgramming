#include "Renderable.h"
#include <SOIL.h>

Renderable::Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices, std::function<void(GLProgram&)> instanceUpdate,
	GLint drawMode ) :
	program(program), vertexBuffer(vertexBuffer),
	indexBuffer(indexBuffer), vertexArrayObject(vertexArrayObject), numberOfIndices(numberOfIndices), drawMode(drawMode),
	instanceUpdate(instanceUpdate)
{

}
GLuint Renderable::GetDrawMode() const noexcept
{
	return drawMode;
}
GLuint Renderable::GetVertexBuffer()const noexcept
{
	return vertexBuffer;
}

GLuint Renderable::GetIndexBuffer()const noexcept
{
	return indexBuffer;
}

GLuint Renderable::GetVertexArrayObject()const noexcept
{
	return vertexArrayObject;
}

GLuint Renderable::GetIndicesCount() const noexcept
{
	return numberOfIndices;
}

void Renderable::Update()
{
	for (auto i = 0u; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}
	program.Update();
	instanceUpdate(program);
}

void Renderable::FlipY(unsigned char * image, int width, int height, int channels)
{
	for (size_t h = 0; h * 2 < height; h++)
	{
		auto pixel1 = h * width * channels;
		auto pixel2 = (height - 1 - h) * width * channels;
		for (size_t w = width * channels; w > 0; w--)
		{
			auto temp = image[pixel1];
			image[pixel1] = image[pixel2];
			image[pixel2] = temp;
			pixel1++;
			pixel2++;
		}
	}
}

void Renderable::AddTexture(const char * filePath)
{
	auto width = 0, height = 0, channels = 0;
	auto imageBytes = SOIL_load_image(filePath, &width, &height, &channels,SOIL_LOAD_AUTO);

	if (imageBytes != nullptr)
	{
		FlipY(imageBytes,width, height, channels);
		GLuint textureId;
		glActiveTexture(GL_TEXTURE0 + textures.size());
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexStorage2D(GL_TEXTURE_2D, 1, (channels == 3) ? GL_RGB8 : GL_RGBA8, width, height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, (channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageBytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		delete[] imageBytes;

		textures.push_back(textureId);
	}
	
}