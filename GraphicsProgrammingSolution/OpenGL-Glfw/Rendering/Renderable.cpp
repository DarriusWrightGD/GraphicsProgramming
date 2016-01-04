#include "Renderable.h"
#include <SOIL.h>
#include <Exceptions\FileNotFoundException.h>
#include <Rendering\GLRenderer.h>
#include <Util\ServiceLocator.h>
#include <Rendering\RenderUtil.h>
Renderable::Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices, std::vector<UniformUpdate> uniforms,
	GLint drawMode, DrawFunction function ) :
	program(program), vertexBuffer(vertexBuffer),
	indexBuffer(indexBuffer), vertexArrayObject(vertexArrayObject), numberOfIndices(numberOfIndices), drawMode(drawMode),
	function(function)
{
	renderer = Services.Get<GLRenderer>();
	instanceUniforms.resize(uniforms.size());
	std::move(uniforms.begin(), uniforms.end(), instanceUniforms.begin());
}
GLint Renderable::GetTextureCount()
{
	return textures.size();
}
GLuint Renderable::GetDrawMode() const noexcept
{
	return drawMode;
}
GLuint Renderable::GetVertexBuffer()const noexcept
{
	return vertexBuffer;
}

DrawFunction Renderable::GetDrawFunction() const noexcept
{
	return function;
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
		glBindTexture(textures[i].type, textures[i].id);
		glBindSampler(i, textures[i].sampler);
	}
	program.Update();
	for (auto uniform : instanceUniforms)
	{
		program.UpdateUniform(uniform.name, { uniform.type, uniform.value });
	}
}

TextureInfo Renderable::AddTexture(const char * filePath, SamplerType samplerType)
{
	auto texture = renderer->CreateTexture(textures.size(), filePath, samplerType);
	AddTexture(texture);
	return texture;
}

void Renderable::AddTexture(TextureInfo texture)
{
	textures.push_back(texture);
}


const char * suffixes[] = {
	"posx", "negx",
	"posy", "negy",
	"posz", "negz",
};

const GLuint targets[] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

TextureInfo Renderable::AddCubeMap(const char * folderPath, const char * extension)
{
	GLuint textureId;
	glActiveTexture(GL_TEXTURE0 + textures.size());
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	GLint w, h, channels;
	for (auto i = 0u; i < 6; i++)
	{
		auto path = (std::string(folderPath) + "/" + suffixes[i] + "." + extension);
		auto image = SOIL_load_image(path.c_str(), &w, &h, &channels, SOIL_LOAD_AUTO);
		
		if (image == nullptr)
		{
			throw FileNotFoundException(path.c_str());
		}
		
		if (i == 0)
		{
			glTexStorage2D(GL_TEXTURE_CUBE_MAP, 1, GL_RGB8, w, h);
		}
		glTexSubImage2D(targets[i], 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, image);
		delete[] image;
	}

	textures.push_back({ textureId ,GL_TEXTURE_CUBE_MAP, renderer->GetSampler(SamplerType::Cubemap).sampler });
	return textures[textures.size()-1];
}
