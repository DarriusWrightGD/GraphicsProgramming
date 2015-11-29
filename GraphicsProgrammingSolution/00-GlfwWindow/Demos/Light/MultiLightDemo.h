#pragma once
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\MeshComponent.h>
#include <Components\TransformComponent.h>
#include <Data\Light.h>
#include <memory>

class MultiLightDemo : public GlfwWindow
{
public:
	MultiLightDemo();
	~MultiLightDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<GameObject> monkey;
	std::unique_ptr<MeshComponent> mesh;
	GLProgram program;
	PointLight lights[3];
};
