#pragma once
#include <GL\gl_core_4_5.h>
#include <vector>
#include <functional>
#include <Rendering\GLSampler.h>
#include <Rendering\SamplerType.h>
#include <Rendering\TextureInfo.h>
#include <Rendering\Uniforms.h>
class GLRenderer;
class Renderable
{
public:
	Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices, std::vector<UniformUpdate> uniforms = {},
		GLint drawMode = GL_TRIANGLES);

	GLuint GetDrawMode() const noexcept;
	GLuint GetVertexBuffer()const noexcept;
	GLuint GetIndexBuffer()const noexcept;
	GLuint GetVertexArrayObject()const noexcept;
	GLuint GetIndicesCount() const noexcept;
	
	TextureInfo AddTexture(const char * filePath, SamplerType samplerType = SamplerType::Linear);
	void AddTexture(TextureInfo texture);
	TextureInfo AddCubeMap(const char * folderPath, const char * extension);
	void Update();
	bool visible = true;
private:
	void FlipY(unsigned char * image, int width, int height, int channels);
	void SetWrapParameters(SamplerType samplerType);
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
	GLuint numberOfIndices;
	GLint drawMode;
	std::vector<TextureInfo> textures;
	std::vector<UniformUpdate> instanceUniforms;
	GLProgram & program;
	GLRenderer * renderer;
};

