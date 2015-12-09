#include "Renderable.h"
#include <SOIL.h>
#include <Exceptions\FileNotFoundException.h>
#include <Rendering\GLRenderer.h>
#include <Util\ServiceLocator.h>
Renderable::Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices, std::vector<UniformUpdate> uniforms,
	GLint drawMode ) :
	program(program), vertexBuffer(vertexBuffer),
	indexBuffer(indexBuffer), vertexArrayObject(vertexArrayObject), numberOfIndices(numberOfIndices), drawMode(drawMode)
{
	renderer = Services.Get<GLRenderer>();
	instanceUniforms.resize(uniforms.size());
	std::move(uniforms.begin(), uniforms.end(), instanceUniforms.begin());
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
		glBindTexture(textures[i].type, textures[i].id);
		glBindSampler(i, textures[i].sampler);
	}
	program.Update();
	for (auto uniform : instanceUniforms)
	{
		program.UpdateUniform(uniform.name, { uniform.type, uniform.value });
	}
}

void Renderable::FlipY(unsigned char * image, int width, int height, int channels)
{
	for (size_t h = 0u; h * 2 < height; h++)
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

void Renderable::SetWrapParameters(SamplerType wrapType)
{
	//switch (wrapType)
	//{
	//case TextureWrapType::Default:
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	break;
	//case TextureWrapType::Cubemap:
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//	break;
	//case TextureWrapType::Projection:
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	//	break;
	//}
}

TextureInfo Renderable::AddTexture(const char * filePath, SamplerType samplerType)
{
	auto width = 0, height = 0, channels = 0;
	auto imageBytes = SOIL_load_image(filePath, &width, &height, &channels,SOIL_LOAD_AUTO);
	TextureInfo texture;
	if (imageBytes != nullptr)
	{
		FlipY(imageBytes,width, height, channels);
		GLuint textureId;

		int colorComponents = GL_RGBA8;;
		int colorChannels = GL_RGBA;;

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

		glActiveTexture(GL_TEXTURE0 + textures.size());
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexStorage2D(GL_TEXTURE_2D, 1, colorComponents, width, height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height,colorChannels, GL_UNSIGNED_BYTE, imageBytes);

		textures.push_back({ textureId ,GL_TEXTURE_2D,renderer->GetSampler(samplerType).sampler });
		texture = textures[textures.size() - 1];
	}	
	else
	{
		throw FileNotFoundException(filePath);
	}

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
/*
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);*/

	textures.push_back({ textureId ,GL_TEXTURE_CUBE_MAP, renderer->GetSampler(SamplerType::Cubemap).sampler });
	return textures[textures.size()-1];
}
