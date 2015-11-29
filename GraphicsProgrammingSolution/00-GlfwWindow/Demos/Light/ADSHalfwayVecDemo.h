#pragma once
#include <GameObjects/GameObject.h>
#include <Components\MeshComponent.h>
#include <Components\TransformComponent.h>
#include <Window\GlfwWindow.h>
#include <memory>
#include <Data\Light.h>

class ADSHalfwayVecDemo : public GlfwWindow
{
public:
	ADSHalfwayVecDemo();
	~ADSHalfwayVecDemo();
	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<GameObject> sphere;
	std::unique_ptr<MeshComponent> mesh;
	GLProgram program;
	PointLight light;
};

