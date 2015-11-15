#include "LoadingObjDemo.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <gtc/constants.hpp>


#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>


LoadingObjDemo::LoadingObjDemo()
{
}


LoadingObjDemo::~LoadingObjDemo()
{
}

void LoadingObjDemo::Update()
{
	modelMatrix *= glm::rotate(0.1f, glm::vec3(0.0f, 1.0f, 0.0f));

}

void LoadingObjDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	//glClearDepth(.5f);
	program.Use();
	program.Update();
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
void LoadingObjDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	PrintUniformInfo();

	//auto value = typeid(decltype(int)).name;
	InitializeObj("Assets/Models/Obj/monkey.obj");

	glClearColor(1.0f, 0.6f, 0.3f, 1.0f);
	


	glViewport(0, 0, width, height);

	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glCreateBuffers(1, &vertexBuffer);
	glNamedBufferData(vertexBuffer, sizeof(FullVertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

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
	
	glCreateBuffers(1, &indexBuffer);
	glNamedBufferData(indexBuffer, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);


	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/uniforms.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/uniforms.frag");
	program.Build();


	
	viewMatrix = glm::lookAt(vec3(4.0f, 4.0f, 6.5f), vec3(0.0f, 0.75f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::translate(glm::vec3(0.0f, 0.0f, -4.0f));
	OnResize(width, height);
	program.AddUniform("model", &modelMatrix[0][0], UniformType::MAT4);

	UniformBufferBlock uniformBufferBlock("TransformBlock", {
		{ "TransformBlock.projection",&projectionMatrix[0][0],sizeof(mat4) },
		{ "TransformBlock.view",&viewMatrix[0][0],sizeof(mat4) },
	});
	program.AddUniformBlock(uniformBufferBlock);


	input->addBinding(GLFW_KEY_UP, [this](InputInfo input) {
		modelMatrix *= glm::translate(glm::vec3(0.0f, 0.0f, 0.01f));
	});
	input->addBinding(GLFW_KEY_DOWN, [this](InputInfo input) {
		modelMatrix *= glm::translate(glm::vec3(0.0f, 0.0f, -0.01f));
	});
	input->addBinding(GLFW_KEY_LEFT, [this](InputInfo input) {
		modelMatrix *= glm::translate(glm::vec3(-0.01f, 0.0f, 0.0f));
	});
	input->addBinding(GLFW_KEY_RIGHT, [this](InputInfo input) {
		modelMatrix *= glm::translate(glm::vec3(0.01f, 0.0f, 0.0f));
	});

	input->addBinding(GLFW_KEY_O, [this](InputInfo input) {
		modelMatrix *= glm::translate(glm::vec3(0.0f, -0.01f, 0.0f));
	});
	input->addBinding(GLFW_KEY_P, [this](InputInfo input) {
		modelMatrix *= glm::translate(glm::vec3(0.0f, 0.01f, 0.0f));
	});
}

void LoadingObjDemo::PrintUniformInfo()
{
	GLint max;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &max);
	cout << "Vertex Uniforms : " << max << endl;
	glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &max);
	cout << "Tessellation Uniforms : " << max << endl;
	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &max);
	cout << "Geometry Uniforms : " << max << endl;
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &max);
	cout << "Fragment Uniforms : " << max << endl;

	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max);
	cout << "\nMax Uniform Block Size : " << max << endl;
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &max);
	cout << "\nMax Uniform Block Bindings : " << max << endl;

}
void LoadingObjDemo::OnResize(int w, int h)
{
	glViewport(0, 0, w, h);
	aspectRatio = (float)w / h;
	projectionMatrix = glm::perspectiveFov(glm::radians(60.0f),
		static_cast<float>(w),static_cast<float>(h), 0.3f, 100.0f);
	program.UpdateUniformBlock("TransformBlock");
}

void LoadingObjDemo::InitializeObj(string filePath)
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(filePath.c_str(),
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_FlipWindingOrder);
	if (scene)
	{
		auto mesh = scene->mMeshes[0];
		vertices.resize(mesh->mNumVertices);
		for (auto i = 0u; i < mesh->mNumVertices; i++)
		{
			auto position = mesh->mVertices[i];
			auto normal = mesh->HasNormals() ? mesh->mNormals[i] : aiVector3D(0, 0, 0);
			auto uv = mesh->HasTextureCoords(i) ? mesh->mTextureCoords[0][i] : aiVector3D(0, 0, 0);
			auto vertex = FullVertex();//{ vec3(position.x,position.y,position.y),vec2(uv.x,uv.y),vec3(normal.x,normal.y,normal.y) };
			
			vertex.position = vec3(position.x, position.y, position.z);
			vertex.uv = vec2(uv.x, uv.y);
			vertex.normal = vec3(normal.x, normal.y, normal.z);

			vertices[i] = vertex;
		}
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
	}
}

void LoadingObjDemo::Shutdown()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}
