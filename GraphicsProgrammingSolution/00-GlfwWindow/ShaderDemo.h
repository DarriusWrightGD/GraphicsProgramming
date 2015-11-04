#pragma once
#include <Window\GlfwWindow.h>
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
	GLuint vertexArray;
};

