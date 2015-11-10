#pragma once
#include <Window\GlfwWindow.h>
#include <OGLC\GLProgram.h>
#include <vec4.hpp>
using glm::vec4;

struct ColorVertex
{
	vec4 position;
	vec4 color;
};

class VertexBufferDemo : public GlfwWindow
{
public:
	VertexBufferDemo();
	~VertexBufferDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	GLProgram program;
	GLuint vao;
	GLuint vertexBuffer;
};

