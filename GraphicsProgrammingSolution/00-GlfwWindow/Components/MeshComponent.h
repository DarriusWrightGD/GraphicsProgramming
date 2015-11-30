#pragma once
#include <assimp\mesh.h>
#include <Components\DrawableComponent.h>
#include <Rendering\GLRenderer.h>
#include <Util\ServiceLocator.h>
#include <Data\Material.h>
class DrawableComponent;
class GameObject;

class MeshComponent : public DrawableComponent
{
public:
	MeshComponent(GameObject * gameObject, aiMesh * mesh,GLProgram & program,std::function<void(GLProgram&)>instanceUpdate);
	~MeshComponent();
	Material & GetMaterial();
	virtual void Update() override;
	virtual void Draw() override;
	void AddTexture(const char * file);
private:
	void InitializeMesh(const aiMesh * mesh, GLProgram & program, std::function<void(GLProgram&)>instanceUpdate);
	Renderable * renderable;
	Material material;
};

