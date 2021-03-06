#pragma once
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\MeshComponent.h>
#include <memory>
#include <Data\Light.h>
class DiffuseDemo : public GlfwWindow
{
public:
	DiffuseDemo();
	~DiffuseDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;
private:
	std::unique_ptr<MeshComponent> monkey;
	std::unique_ptr<MeshComponent> box;
	std::unique_ptr<GameObject> boxObject;
	std::unique_ptr<GameObject> monkeyObject;
	GLProgram program;
	PointLight light;
};

