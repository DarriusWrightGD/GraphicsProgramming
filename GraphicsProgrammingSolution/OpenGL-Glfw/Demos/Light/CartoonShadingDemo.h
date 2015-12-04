#pragma once
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\TransformComponent.h>
#include <Components\MeshComponent.h>
#include <Data\Light.h>

class CartoonShadingDemo : public GlfwWindow
{
public:
	CartoonShadingDemo();
	~CartoonShadingDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<GameObject> monkey;
	std::unique_ptr<MeshComponent> mesh;
	PointLight light;
	GLProgram program;
};

