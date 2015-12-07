#pragma once
#include <OGLC\GLProgram.h>
#include <GameObjects\GameObject.h>
#include <Components\TransformComponent.h>
#include <Components\MeshComponent.h>
#include <Window\GlfwWindow.h>
#include <Data\Light.h>

class ProjectedTextureDemo : public GlfwWindow
{
public:
	ProjectedTextureDemo();
	~ProjectedTextureDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<GameObject> plane;
	std::unique_ptr<MeshComponent> planeMesh;
	std::unique_ptr<GameObject> cube;
	std::unique_ptr<MeshComponent> cubeMesh;

	GLProgram program;
	glm::mat4 projectorMatrix;
	PointLight light;
};

