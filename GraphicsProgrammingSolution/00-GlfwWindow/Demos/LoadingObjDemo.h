#pragma once
#include <Window\GlfwWindow.h>
#include <OGLC\GLProgram.h>
#include <vec3.hpp>
#include <vec2.hpp>
#include <mat4x4.hpp>
#include <iostream>
#include <Components\MeshComponent.h>
#include <GameObjects\GameObject.h>
#include <GLRenderer.h>
#include <memory>
#include "Vertex.h"
using glm::vec2;
using glm::vec3;
using glm::mat4;
using std::cout;
using std::endl;

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
	void InitializeObj(string filePath);
	void PrintUniformInfo();
	std::unique_ptr<MeshComponent> meshComponent;
	std::unique_ptr<GameObject> gameObject;
	GLProgram program;
	GLuint vao;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint transformBuffer;
	GLfloat aspectRatio;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 modelMatrix;


	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	GLRenderer * renderer;

	// Inherited via GlfwWindow
	virtual void OnResize(int width, int height) override;
};

