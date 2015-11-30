#pragma once

#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\MeshComponent.h>
#include <Components\TransformComponent.h>
class MultiTextureDemo : public GlfwWindow
{
public:
	MultiTextureDemo();
	~MultiTextureDemo();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	std::unique_ptr<GameObject> boxObject;
	std::unique_ptr<MeshComponent> boxMesh;
	GLProgram program;
};

