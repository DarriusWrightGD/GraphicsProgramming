#pragma once
#include <assimp\mesh.h>
#include <Components\DrawableComponent.h>
#include <Rendering\GLRenderer.h>
#include <Util\ServiceLocator.h>
class DrawableComponent;
class GameObject;

class MeshComponent : public DrawableComponent
{
public:
	MeshComponent(GameObject * gameObject, aiMesh * mesh,GLProgram & program);
	~MeshComponent();
	virtual void Update() override;
	virtual void Draw() override;

private:
	void InitializeMesh(const aiMesh * mesh, GLProgram & program);
	Renderable * renderable;
};

