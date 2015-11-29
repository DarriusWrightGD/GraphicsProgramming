#include "DirectionalLightDemo.h"



DirectionalLightDemo::DirectionalLightDemo()
{
}


DirectionalLightDemo::~DirectionalLightDemo()
{
}

void DirectionalLightDemo::Update()
{
	monkey->Update();
}

void DirectionalLightDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void DirectionalLightDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm.hpp>
void DirectionalLightDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.1f, 0.4f, 1.0f);
	light.direction = glm::normalize(glm::vec3(0.5, 0.5, -1.0));
	light.color = glm::vec3(0.2,0.8,0.3);

	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/directionalLight.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/directionalLight.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{"TransformBlock.eyePosition", &camera->GetPosition()[0], sizeof(camera->GetPosition())},
	}});

	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.direction", &light.direction[0], sizeof(light.direction) },
		{"LightBlock.color", &light.color[0], sizeof(light.color)}
	} });

	using std::unique_ptr;
	monkey = unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f ,-5.0f });
	monkey->Update();
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = unique_ptr<MeshComponent>(new MeshComponent(monkey.get(), scene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform("world", { UniformType::MAT4,&monkey->GetWorld()[0][0] });
			program.UpdateUniform("material.ambient", { UniformType::VEC3, &mesh->GetMaterial().ambient[0] });
			program.UpdateUniform("material.diffuse", { UniformType::VEC3, &mesh->GetMaterial().diffuse[0] });
			program.UpdateUniform("material.specular", { UniformType::VEC4, &mesh->GetMaterial().specular[0] });
		}));
	}
}

void DirectionalLightDemo::Shutdown()
{
}
