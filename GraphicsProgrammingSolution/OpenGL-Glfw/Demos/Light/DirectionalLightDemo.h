#pragma once
#include <Window\GlfwWindow.h>
#include <Components\MeshComponent.h>
#include <GameObjects\GameObject.h>
#include <Components\TransformComponent.h>
#include <Data\Light.h>
#include <memory>

class DirectionalLightDemo : public GlfwWindow
{
public:
	DirectionalLightDemo();
	~DirectionalLightDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;
private:
	std::unique_ptr<GameObject> monkey;
	std::unique_ptr<MeshComponent> mesh;
	DirectionalLight light;
	GLProgram program;
};

