#include "LoadingObjDemo.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


LoadingObjDemo::LoadingObjDemo()
{
}


LoadingObjDemo::~LoadingObjDemo()
{
}

void LoadingObjDemo::Update()
{
}

void LoadingObjDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void LoadingObjDemo::Initialize()
{
	InitializeObj("Assets/Models/Obj/box.obj");
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vertexBuffer);
	glCreateBuffers(1, &indexBuffer);

	glNamedBufferData(indexBuffer, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glNamedBufferData(vertexBuffer, sizeof(FullVertex) * vertices.size(), &vertices, GL_STATIC_DRAW);

	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 1, 2, GL_FLOAT, GL_FALSE, sizeof(vec3));

	glVertexArrayAttribBinding(vao, 2, 0);
	glVertexArrayAttribFormat(vao, 2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) + sizeof(vec2));

	glVertexArrayVertexBuffer(vao, 0, vertexBuffer, 0, sizeof(FullVertex));
	glVertexArrayVertexBuffer(vao, 1, vertexBuffer, sizeof(vec3), sizeof(FullVertex));
	glVertexArrayVertexBuffer(vao, 2, vertexBuffer, sizeof(vec3) + sizeof(vec2), sizeof(FullVertex));

	glEnableVertexArrayAttrib(vao, 0);
	glEnableVertexArrayAttrib(vao, 1);
	glEnableVertexArrayAttrib(vao, 2);
}

void LoadingObjDemo::InitializeObj(string filePath)
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(filePath.c_str(),
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals);
	if (scene)
	{
		auto mesh = scene->mMeshes[0];
		vertices.resize(mesh->mNumVertices);
		for (auto i = 0; i < mesh->mNumVertices; i++)
		{
			auto position = mesh->mVertices[i];
			auto normal = (mesh->HasNormals) ? mesh->mNormals[i] : aiVector3D(0, 0, 0);
			auto uv = (mesh->HasTextureCoords) ? mesh->mTextureCoords[0][i] : aiVector3D(0, 0, 0);
			vertices.push_back({ vec3(position.x,position.y,position.y),vec2(uv.x,uv.y),vec3(normal.x,normal.y,normal.y) });
		}
		indices.resize(mesh->mNumFaces * 3);
		for (auto i = 0; i < mesh->mNumFaces; i++)
		{
			auto face = mesh->mFaces[i];
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		delete scene;
	}
}

void LoadingObjDemo::Shutdown()
{
}
