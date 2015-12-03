#pragma once
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\TransformComponent.h>
#include <Components\MeshComponent.h>
class CubemapDemo : public GlfwWindow
{
public:
	CubemapDemo();
	~CubemapDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	GLProgram program;
	std::unique_ptr<GameObject> box;
	std::unique_ptr<MeshComponent> mesh;

};

