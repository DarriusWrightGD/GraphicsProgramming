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
	TextureInfo AddTexture(const char * file, TextureWrapType wrapType = TextureWrapType::Default);
	void AddTexture(TextureInfo texture);
	TextureInfo AddCubeMap(const char * folderPath, const char * extension);
private:
	GLRenderer * renderer = nullptr;
	Renderable * renderable;
	Material material;
	bool initialized = false;
};

