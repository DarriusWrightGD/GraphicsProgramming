#include "Renderable.h"


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

#include <SOIL.h>

void Renderable::AddTexture(const char * filePath)
{
	auto width = 0, height = 0, channels = 0;
	auto imageBytes = SOIL_load_image("Assets/Textures/brick.jpg", &width, &height, &channels, SOIL_LOAD_RGB);
	//program.Use();
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