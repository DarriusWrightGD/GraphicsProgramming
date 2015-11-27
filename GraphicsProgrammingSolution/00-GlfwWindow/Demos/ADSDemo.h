#pragma once
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\MeshComponent.h>
#include <Components\TransformComponent.h>
#include <Data\Light.h>

class ADSDemo : public GlfwWindow
{
public:
	ADSDemo();
	~ADSDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<GameObject> monkeyObject;
	std::unique_ptr<MeshComponent> monkeyMesh;
	GLProgram program;
	PointLight light;
};

