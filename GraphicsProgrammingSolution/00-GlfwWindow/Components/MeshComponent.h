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
	MeshComponent(GameObject * gameObject);
	~MeshComponent();
	void Initialize(const aiMesh * mesh, GLProgram & program, const std::vector<UniformUpdate> & instanceUniforms);
	Material & GetMaterial();
	virtual void Update() override;
	virtual void Draw() override;
	void AddTexture(const char * file);
private:
	Renderable * renderable;
	Material material;
	bool initialized = false;
};

