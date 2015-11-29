#pragma once
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\TransformComponent.h>
#include <Components\MeshComponent.h>
#include <memory>
#include <Data\Light.h>

class SpotLightDemo : public GlfwWindow
{
public:
	SpotLightDemo();
	~SpotLightDemo();



	// Inherited via GlfwWindow
	virtual void Update() override;

	virtual void Render() override;

	virtual void OnResize(int width, int height) override;

	virtual void Initialize() override;

	virtual void Shutdown() override;
private:
	GLProgram program;
	std::unique_ptr<GameObject> monkey;
	std::unique_ptr<MeshComponent> mesh;
	SpotLight light;
};

