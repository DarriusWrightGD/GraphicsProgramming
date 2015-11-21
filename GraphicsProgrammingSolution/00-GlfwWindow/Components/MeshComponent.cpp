#include "MeshComponent.h"
#include <GameObjects\GameObject.h>

#include <GLRenderer.h>

#include <Vertex.h>
#include <vec3.hpp>
#include <vec2.hpp>
using glm::vec3;
using glm::vec2;

/*There needs to be a clear separation where 
the mesh can be completely abstracted from from the renderer
therefore you should pull the data in only to forward it to a render layer with
the appropriate placements
*/

MeshComponent::MeshComponent(GameObject * gameObject, aiMesh * mesh,GLProgram & program) : DrawableComponent(gameObject) 
{
	InitializeMesh(mesh, program);
}

MeshComponent::~MeshComponent()
{
	
}

void MeshComponent::Update()
{
}

void MeshComponent::Draw()
{
}

void MeshComponent::InitializeMesh(const aiMesh * mesh, GLProgram & program)
{
	auto renderer = Services.Get<GLRenderer>();
	if (renderer != nullptr)
	{
		std::vector<Vertex> vertices;
		vertices.resize(mesh->mNumVertices);
		for (auto i = 0u; i < mesh->mNumVertices; i++)
		{
			auto position = mesh->mVertices[i];
			auto normal = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D(0, 0, 0);
			auto uv = mesh->HasTextureCoords(i) ? mesh->mTextureCoords[0][i] : aiVector3D(0, 0, 0);
			auto vertex = Vertex();

			vertex.position = vec3(position.x, position.y, position.z);
			vertex.uv = vec2(uv.x, uv.y);
			vertex.normal = vec3(normal.x, normal.y, normal.z);

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

		renderable = &renderer->AddRenderable(program,VertexBufferLayout(&vertices[0], vertices.size(), &indices[0], indices.size(), sizeof(Vertex)),{ 
			{ 3,offsetof(Vertex,position) },
			{ 3,offsetof(Vertex,normal) },
			{ 2,offsetof(Vertex,uv) }
		});

		indices.clear();
		vertices.clear();
	}
}
