#include "NormalMapDemo.h"



NormalMapDemo::NormalMapDemo()
{
}


NormalMapDemo::~NormalMapDemo()
{
}

void NormalMapDemo::Update()
{
	ogre->Update();
}

void NormalMapDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void NormalMapDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\postprocess.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>

void NormalMapDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/normal-map.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/normal-map.frag");
	program.Build();

	light.position = glm::vec3(0.0f, 0.0f, 1.0f);
	light.color = glm::vec3(0.8f,0.8f,0.8f);

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view",&camera->GetView()[0][0], sizeof(camera->GetView()) },
		{"TransformBlock.projection",&camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{"TransformBlock.eyePosition", &camera->GetPosition()[0], sizeof(camera->GetPosition())}
	} });

	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.position", &light.position[0], sizeof(light.position) },
		{"LightBlock.color", &light.color[0], sizeof(light.color)},
	} });

	ogre = std::unique_ptr<GameObject>(new GameObject());
	ogre->GetTransform()->SetPosition({ 0.0f,0.0f,-3.0f });
	ogre->Update();

	input->addBinding(GLFW_KEY_LEFT, [this](InputInfo info) {
		camera->MoveLeft();
		program.UpdateUniformBlock("TransformBlock");
	});

	input->addBinding(GLFW_KEY_RIGHT, [this](InputInfo info) {
		camera->MoveRight();
		program.UpdateUniformBlock("TransformBlock");
	});


	input->addBinding(GLFW_KEY_UP, [this](InputInfo info) {
		camera->MoveForward();
		program.UpdateUniformBlock("TransformBlock");
	});

	input->addBinding(GLFW_KEY_DOWN, [this](InputInfo info) {
		camera->MoveBack();
		program.UpdateUniformBlock("TransformBlock");
	});

	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/ogre.obj", aiProcess_Triangulate | aiProcess_CalcTangentSpace );
	if (scene && scene->HasMeshes())
	{
		mesh = std::unique_ptr<MeshComponent>(new MeshComponent(ogre.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{"world",UniformType::MAT4, &ogre->GetWorld()[0][0]},
			{ "material.ambient", UniformType::VEC3, &mesh->GetMaterial().ambient[0] },
			{"material.specular", UniformType::VEC4, &mesh->GetMaterial().specular[0]},
		});
		mesh->GetMaterial().ambient = glm::vec3(0.5f, 0.5f, 0.5f);
		mesh->GetMaterial().specular = glm::vec4(.4f, .2f, .7f,4.0f);

		mesh->AddTexture("Assets/Textures/ogre_diffuse.png");
		mesh->AddTexture("Assets/Textures/ogre_normal.png");

		ogre->AddComponent(mesh.get());
	}

}

void NormalMapDemo::Shutdown()
{
}
