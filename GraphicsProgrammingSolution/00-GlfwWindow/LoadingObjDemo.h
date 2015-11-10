#pragma once
#include <Window\GlfwWindow.h>
#include <vec3.hpp>
#include <vec2.hpp>
using glm::vec2;
using glm::vec3;
struct FullVertex
{
	vec3 position;
	vec2 uv;
	vec3 normal;
};

class LoadingObjDemo : public GlfwWindow
{
public:
	LoadingObjDemo();
	~LoadingObjDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	GLuint vao;
	GLuint vertexBuffer;
	std::vector<FullVertex> vertices;
	std::vector<int> indices;
};

