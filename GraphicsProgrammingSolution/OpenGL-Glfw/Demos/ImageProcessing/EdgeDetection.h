#pragma once
#include <Rendering\GLRenderer.h>
#include <Rendering\Renderable.h>
#include <Window\GlfwWindow.h>
#include <GameObjects\GameObject.h>
#include <Components\MeshComponent.h>
#include <Components\TransformComponent.h>

class EdgeDetection : public GlfwWindow
{
public:
	EdgeDetection();
	~EdgeDetection();

	// Inherited via GlfwWindow
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnResize(int width, int height) override;
	virtual void Initialize() override;
	virtual void Shutdown() override;

private:
	RenderPass * pass;
	GLProgram program;
	GLProgram guiProgram;
	std::unique_ptr<GameObject> monkey;
	std::unique_ptr<MeshComponent> mesh;
};

