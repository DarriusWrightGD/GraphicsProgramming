#pragma once
#include <Window\GlfwWindow.h>
#include <OGLC\GLProgram.h>

class ShaderColorDemo : public GlfwWindow
{
public:
	ShaderColorDemo();
	~ShaderColorDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void Shutdown() override;
private:
	GLProgram program;
	GLuint vertexArray;


	// Inherited via GlfwWindow
	virtual void OnResize(int width, int height) override;

};

