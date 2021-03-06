#pragma once

#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\Component.h>
#include <Components\TransformComponent.h>
#include <Components\MeshComponent.h>

class FrameBufferDemo : public GlfwWindow
{
public:
	FrameBufferDemo();
	~FrameBufferDemo();


	// Inherited via GlfwWindow
	virtual void Update() override;

	virtual void Render() override;

	virtual void OnResize(int width, int height) override;

	virtual void Initialize() override;

	virtual void Shutdown() override;

private:
	GLProgram fboProgram;
	GLProgram textureProgram;
	std::unique_ptr<GameObject> cube;
	std::unique_ptr<GameObject> monkey;

	std::unique_ptr<MeshComponent> cubeMesh;
	std::unique_ptr<MeshComponent> monkeyMesh;

	GLuint fboHandle;
	GLuint depthBufferTexture;
	GLuint renderTargetTexture;
};

