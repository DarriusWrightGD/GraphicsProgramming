#include "CartoonShadingDemo.h"



CartoonShadingDemo::CartoonShadingDemo()
{
}


CartoonShadingDemo::~CartoonShadingDemo()
{
}

void CartoonShadingDemo::Update()
{
	monkey->Update();
}

void CartoonShadingDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void CartoonShadingDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

void CartoonShadingDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	light.color = glm::vec3(0.8f, 0.8f, 0.8f);
	light.position = glm::vec3(2.0f, 0.0f, -2.0f);

	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/cartoonEffect.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/cartoonEffect.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{"TransformBlock.eyePosition", &camera->GetPosition()[0], sizeof(camera->GetPosition())},
	}});

	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.color", &light.color[0], sizeof(light.color) },
		{"LightBlock.position", &light.position[0], sizeof(light.position)}
	} });

	using std::unique_ptr;
	monkey = unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f,-3.0f });
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj",aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = unique_ptr<MeshComponent>(new MeshComponent(monkey.get(), scene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform("world", { UniformType::MAT4,&monkey->GetWorld()[0][0] });
			program.UpdateUniform("material.ambient", { UniformType::VEC3, &mesh->GetMaterial().ambient[0] });
			program.UpdateUniform("material.diffuse", { UniformType::VEC3, &mesh->GetMaterial().diffuse[0] });
			program.UpdateUniform("material.specular", { UniformType::VEC4, &mesh->GetMaterial().specular[0] });
		}));
		monkey->AddComponent(mesh.get());

		mesh->GetMaterial().ambient = glm::vec3(0.4f, 0.7f, 0.1f);
		mesh->GetMaterial().diffuse = glm::vec3(0.9f, 0.1f, 0.1f);
		mesh->GetMaterial().specular = glm::vec4(0.1f, 0.4f, 0.5f,10.0f);
	}
	importer.FreeScene();

}

void CartoonShadingDemo::Shutdown()
{
}
