#pragma once
#include <Window\GlfwWindow.h>
#include <OGLC\GLProgram.h>

class ShaderDemo : public GlfwWindow
{
public:
	ShaderDemo();
	~ShaderDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;

private:
	void BuildProgram();
	virtual void Shutdown() override;

	GLuint vertexShader;
	GLuint fragmentShader;
	GLint program;
	GLProgram glProgram;
	GLuint vertexArray;

	// Inherited via GlfwWindow
	virtual void OnResize(int width, int height) override;
};

