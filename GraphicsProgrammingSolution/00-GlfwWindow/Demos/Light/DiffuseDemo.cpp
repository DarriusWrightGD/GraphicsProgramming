#include "DiffuseDemo.h"
#include <assimp\scene.h>
#include <Components\TransformComponent.h>
#include <assimp\Importer.hpp>
#include<assimp\postprocess.h>
#include <mat4x4.hpp>

DiffuseDemo::DiffuseDemo() 
{
}


DiffuseDemo::~DiffuseDemo()
{
}

void DiffuseDemo::Update()
{
	monkeyObject->Update();
	boxObject->Update();
}

void DiffuseDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void DiffuseDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / height);
	program.UpdateUniformBlock("TransformBlock");
}
void DiffuseDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.7f, 0.2f, 1.0f);

	program.Initialize();
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/diffuseLight.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/diffuseLight.frag");
	program.Build();

	light.position = glm::vec3(5.0f, 5.0f, -5.0f);
	light.color = glm::vec3(0.0f, 0.5f, 0.5f);

	
	program.AddUniformBlock({
		"TransformBlock",{
			{ "TransformBlock.view", &camera->GetView()[0][0],sizeof(camera->GetView()) },
			{ "TransformBlock.projection", &camera->GetProjection()[0][0],sizeof(camera->GetProjection()) }
		}
	});

	program.AddUniformBlock({
		"LightBlock", {
			{ "LightBlock.position", &light.position[0],sizeof(light.position) },
			{ "LightBlock.color", &light.color[0],sizeof(light.color) }
		}
	});
	
	monkeyObject = std::unique_ptr<GameObject>(new GameObject());
	boxObject = std::unique_ptr<GameObject>(new GameObject());


	monkeyObject->GetTransform()->SetPosition(glm::vec3(0, 0, -5));
	monkeyObject->GetTransform()->Update();

	boxObject->GetTransform()->SetPosition(glm::vec3(2, 2, -7));
	boxObject->GetTransform()->Update();

	program.AddUniform("view", &camera->GetView()[0][0], UniformType::MAT4);
	program.AddUniform("projection", &camera->GetProjection()[0][0], UniformType::MAT4);

	Assimp::Importer importer;
	auto monkeyScene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	if (monkeyScene)
	{
		monkey = std::unique_ptr<MeshComponent>(new MeshComponent(monkeyObject.get(), monkeyScene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform(program.GetUniformLocation("world"), {UniformType::MAT4,&monkeyObject->GetWorld()[0][0] });
			program.UpdateUniform(program.GetUniformLocation("diffuse"), { UniformType::VEC3,&monkey->GetMaterial().diffuse[0] });

		}));
		monkeyObject->AddComponent(monkey.get());
	}
	importer.FreeScene();

	auto boxScene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);
	if (boxScene)
	{
		box = std::unique_ptr<MeshComponent>(new MeshComponent(boxObject.get(), boxScene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform(program.GetUniformLocation("world"), { UniformType::MAT4,&boxObject->GetWorld()[0][0] });
			program.UpdateUniform(program.GetUniformLocation("diffuse"), { UniformType::VEC3,&box->GetMaterial().diffuse[0] });

		}));
		box->GetMaterial().diffuse = glm::vec3(0.2f, 0.7f, 0.5);
		boxObject->AddComponent(box.get());
	}

	importer.FreeScene();

}


void DiffuseDemo::Shutdown()
{
}
