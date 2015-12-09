#pragma once
#include <assimp\mesh.h>
#include <Components\DrawableComponent.h>
#include <Util\ServiceLocator.h>
#include <Data\Material.h>
#include <OGLC\GLProgram.h>
#include <Rendering\TextureInfo.h>
#include <Rendering\GLSampler.h>
#include <Rendering\SamplerType.h>
#include <Rendering\Renderable.h>
#include <Rendering\GLRenderer.h>

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
	Renderable * GetRenderable();
	TextureInfo AddTexture(const char * file, SamplerType wrapType = SamplerType::Linear);
	void AddTexture(TextureInfo texture);
	TextureInfo AddCubeMap(const char * folderPath, const char * extension);
private:
	GLRenderer * renderer = nullptr;
	Renderable * renderable;
	Material material;
	bool initialized = false;
};

