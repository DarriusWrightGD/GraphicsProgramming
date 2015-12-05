#pragma once
#include <OGLC\GLProgram.h>
#include <GameObjects\GameObject.h>
#include <Components\TransformComponent.h>
#include <Components\MeshComponent.h>
#include <Window\GlfwWindow.h>

class ProjectedTextureDemo
{
public:
	ProjectedTextureDemo();
	~ProjectedTextureDemo();

private:
	std::unique_ptr<GameObject> plane;
	std::unique_ptr<MeshComponent> planeMesh;
	std::unique_ptr<GameObject> cube;
	std::unique_ptr<MeshComponent> cubeMesh;

};

