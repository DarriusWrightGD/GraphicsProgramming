#pragma once
#include <Window\GlfwWindow.h>
#include <Components\MeshComponent.h>
#include <Components\TransformComponent.h>
#include <GameObjects\GameObject.h>
class AlphaMapDemo : public GlfwWindow
{
public:
	AlphaMapDemo();
	~AlphaMapDemo();

private:
	std::unique_ptr<GameObject> box;
	std::unique_ptr<MeshComponent> mesh;
	GLProgram program;

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;
};

