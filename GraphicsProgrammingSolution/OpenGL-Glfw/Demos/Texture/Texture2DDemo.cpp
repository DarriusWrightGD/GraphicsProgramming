#include "Texture2DDemo.h"
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <OGLC\GLProgram.h>
#include <SOIL.h>

Texture2DDemo::Texture2DDemo()
{
}


Texture2DDemo::~Texture2DDemo()
{
}

void Texture2DDemo::Update()
{
	boxObject->Update();
}

void Texture2DDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void Texture2DDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}
void Texture2DDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/texture.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/texture.frag");
	program.Build();



	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view",&camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection",&camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
	} });

	using std::unique_ptr;
	boxObject = unique_ptr<GameObject>(new GameObject());
	Assimp::Importer importer;
	boxObject->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	boxObject->Update();
	auto scene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);

	if (scene && scene->HasMeshes())
	{
		boxMesh = unique_ptr<MeshComponent>(new MeshComponent(boxObject.get()));
		boxMesh->Initialize(scene->mMeshes[0], program, {
			{ "world", UniformType::MAT4,&boxObject->GetWorld()[0][0] }
		});
		boxMesh->AddTexture("Assets/Textures/brick.jpg");
		boxObject->AddComponent(boxMesh.get());
	}
}

void Texture2DDemo::Shutdown()
{
}
