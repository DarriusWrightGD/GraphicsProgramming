#pragma once
#include <Components\DrawableComponent.h>
#include <assimp\mesh.h>
class MeshComponent : public DrawableComponent
{
public:
	MeshComponent(GameObject * gameObject, aiMesh * mesh);
	~MeshComponent();
private:
	virtual void Update() override;
	virtual void Draw() override;
};

