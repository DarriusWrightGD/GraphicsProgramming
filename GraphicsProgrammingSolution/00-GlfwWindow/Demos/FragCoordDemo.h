#pragma once
#include <Window\GlfwWindow.h>
#include <OGLC\GLProgram.h>
class FragCoordDemo : public GlfwWindow
{
public:
	FragCoordDemo();
	~FragCoordDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	GLProgram program;
	GLuint vertexArray;
};

