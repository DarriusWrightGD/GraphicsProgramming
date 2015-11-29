#include "ADSDemo.h"
#include <assimp\postprocess.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>

ADSDemo::ADSDemo()
{
}


ADSDemo::~ADSDemo()
{
}

void ADSDemo::Update()
{
	monkeyObject->Update();
}

void ADSDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void ADSDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width)/static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

void ADSDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/ads.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/ads.frag");
	program.Build();

	light.position = glm::vec3(0.0f, 0.0f, -2.0f);
	light.color = glm::vec3(0.3f, 0.7f, 1.0f);

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view",&camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection",&camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{ "TransformBlock.eyePosition",&camera->GetPosition()[0], sizeof(camera->GetPosition())},
	}});

	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.position",&light.position[0], sizeof(light.position) },
		{"LightBlock.color",&light.color[0], sizeof(light.color) },
	} });

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

	monkeyObject = std::unique_ptr<GameObject>(new GameObject());

	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj",aiProcess_Triangulate);
	monkeyObject->GetTransform()->SetPosition({ -3.0f,0.0f,-5.0f });
	monkeyObject->Update();
	if (scene && scene->HasMeshes())
	{
		monkeyMesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkeyObject.get(), scene->mMeshes[0], program, [this](GLProgram &) {
			program.UpdateUniform("world", { UniformType::MAT4, &monkeyObject->GetTransform()->GetWorld()[0][0] });
			program.UpdateUniform("material.diffuse", { UniformType::VEC3, &monkeyMesh->GetMaterial().diffuse[0] });
			program.UpdateUniform("material.ambient", { UniformType::VEC3, &monkeyMesh->GetMaterial().ambient[0] });
			program.UpdateUniform("material.specular", { UniformType::VEC4, &monkeyMesh->GetMaterial().specular[0] });
		}));
		
		monkeyMesh->GetMaterial().ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		monkeyMesh->GetMaterial().diffuse = glm::vec3(0.8f, 0.2f, 0.2f);
		monkeyMesh->GetMaterial().specular = glm::vec4( 0.8f,0.1f,0.3f,1.0f );
	}
}

void ADSDemo::Shutdown()
{
}
