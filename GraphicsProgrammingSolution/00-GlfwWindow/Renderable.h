#pragma once
#include <GL\gl_core_4_5.h>
#include <OGLC\GLProgram.h>
#include <vector>
#include <functional>

struct Renderable
{
public:
	Renderable(GLProgram & program, GLuint vertexArrayObject, GLuint vertexBuffer, GLuint indexBuffer, GLuint numberOfIndices, std::function<void(GLProgram&)> instanceUpdate,
		GLint drawMode = GL_TRIANGLES);

	GLuint GetDrawMode() const noexcept;
	GLuint GetVertexBuffer()const noexcept;
	GLuint GetIndexBuffer()const noexcept;
	GLuint GetVertexArrayObject()const noexcept;
	GLuint GetIndicesCount() const noexcept;
	
	void AddTexture(const char * filePath);
	void Update();
	bool visible = true;
private:
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint vertexArrayObject;
	GLuint numberOfIndices;
	GLint drawMode;
	std::vector<GLuint> textures;
	GLProgram & program;
	std::function<void(GLProgram&)> instanceUpdate;
};

