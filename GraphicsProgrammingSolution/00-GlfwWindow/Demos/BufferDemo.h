#pragma once
#include <Window/GlfwWindow.h>
#include <OGLC\GLProgram.h>
class BufferDemo : public GlfwWindow
{
public:
	BufferDemo();
	~BufferDemo();
	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void Shutdown() override;
private:
	GLuint vertexArray;
	GLuint positionBuffer;
	GLuint colorBuffer;
	GLuint positionBuffer2;
	GLProgram program;
};

