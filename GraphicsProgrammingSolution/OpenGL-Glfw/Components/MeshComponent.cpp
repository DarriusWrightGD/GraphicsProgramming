#include "MeshComponent.h"
#include <GameObjects\GameObject.h>

#include <Rendering\GLRenderer.h>

#include <Data\Vertex.h>
#include <vec3.hpp>
#include <vec2.hpp>
using glm::vec3;
using glm::vec2;

/*There needs to be a clear separation where 
the mesh can be completely abstracted from from the renderer
therefore you should pull the data in only to forward it to a render layer with
the appropriate placements
*/

MeshComponent::MeshComponent(GameObject * gameObject) : DrawableComponent(gameObject),
material({glm::vec3(0.4f),glm::vec3(0.4f),glm::vec4(0.4f)}), initialized(false)
{
}

MeshComponent::~MeshComponent()
{
	
}

Material & MeshComponent::GetMaterial()
{
	return material;
}

void MeshComponent::Update()
{
}

void MeshComponent::Draw()
{
	if (renderer != nullptr)
	{
		renderer->Render(renderable);
	}
}

TextureInfo MeshComponent::AddTexture(const char * file)
{
	return renderable->AddTexture(file);
}

void MeshComponent::AddTexture(TextureInfo texture)
{
	renderable->AddTexture(texture);
}

TextureInfo MeshComponent::AddCubeMap(const char * folderPath, const char * extension)
{
	return renderable->AddCubeMap(folderPath, extension);
}

void MeshComponent::Initialize(const aiMesh * mesh, GLProgram & program , const std::vector<UniformUpdate> & instanceUniforms)
{
	renderer = Services.Get<GLRenderer>();
	if (renderer != nullptr && !initialized)
	{
		std::vector<Vertex> vertices;
		vertices.resize(mesh->mNumVertices);
		for (auto i = 0u; i < mesh->mNumVertices; i++)
		{
			auto position = mesh->mVertices[i];
			auto normal = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D(0, 0, 0);
			auto uv = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : aiVector3D(0, 0, 0);
			auto tangent = mesh->HasTangentsAndBitangents() ? mesh->mTangents[i] : aiVector3D(0, 0, 0);
			auto biTangent = mesh->HasTangentsAndBitangents() ? mesh->mBitangents[i] : aiVector3D(0, 0, 0);
			auto vertex = Vertex();

			vertex.position = vec3(position.x, position.y, position.z);
			vertex.uv = vec2(uv.x, uv.y);
			vertex.normal = vec3(normal.x, normal.y, normal.z);
			vertex.tangent = vec3(tangent.x, tangent.y, tangent.z);
			vertex.biTangent = vec3(biTangent.x,biTangent.y,biTangent.z);

			vertices[i] = vertex;
		}
		std::vector<GLuint> indices;
		indices.resize(mesh->mNumFaces * 3);
		auto index = 0;
		for (auto i = 0u; i < mesh->mNumFaces; i++)
		{
			auto face = mesh->mFaces[i];
			for (auto j = 0u; j < face.mNumIndices; j++)
			{
				indices[index++] = face.mIndices[j];
			}
		}

		renderable = &renderer->AddRenderable(program,VertexBufferLayout(&vertices[0], vertices.size(), &indices[0], indices.size() , sizeof(Vertex)),{ 
			{ 3,offsetof(Vertex,position) },
			{ 3,offsetof(Vertex,normal) },
			{ 2,offsetof(Vertex,uv) },
			{ 3,offsetof(Vertex,tangent) },
			{ 3,offsetof(Vertex,biTangent) },
			},
			instanceUniforms
		);

		indices.clear();
		vertices.clear();
		initialized = true;
	}
}
