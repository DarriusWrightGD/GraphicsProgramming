#pragma once
#include <GL\gl_core_4_5.h>
#include <OGLC\GLProgram.h>
#include <vector>
#include <functional>

struct UniformUpdate
{
	const char * name;
	UniformType type;
	float * value;
};

struct TextureInfo
{
	GLuint id;
	GLint type;
};

struct Renderable
{
public:
	Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices, std::vector<UniformUpdate> uniforms = {},
		GLint drawMode = GL_TRIANGLES);

	GLuint GetDrawMode() const noexcept;
	GLuint GetVertexBuffer()const noexcept;
	GLuint GetIndexBuffer()const noexcept;
	GLuint GetVertexArrayObject()const noexcept;
	GLuint GetIndicesCount() const noexcept;
	
	void AddTexture(const char * filePath);
	void AddCubeMap(const char * folderPath, const char * extension);
	void Update();
	bool visible = true;
private:
	void FlipY(unsigned char * image, int width, int height, int channels);
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
	GLuint numberOfIndices;
	GLint drawMode;
	std::vector<TextureInfo> textures;
	std::vector<UniformUpdate> instanceUniforms;
	GLProgram & program;

};

