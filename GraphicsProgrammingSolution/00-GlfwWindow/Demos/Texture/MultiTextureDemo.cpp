#include "MultiTextureDemo.h"



MultiTextureDemo::MultiTextureDemo()
{
}


MultiTextureDemo::~MultiTextureDemo()
{
}

void MultiTextureDemo::Update()
{
	boxObject->Update();
}

void MultiTextureDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void MultiTextureDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

void MultiTextureDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/multiTexture.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/multiTexture.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
	}});
	using std::unique_ptr;
	boxObject = unique_ptr<GameObject>(new GameObject());
	boxObject->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	boxObject->Update();

	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);

	if (scene && scene->HasMeshes())
	{
		boxMesh = unique_ptr<MeshComponent>(new MeshComponent(boxObject.get()));
		boxMesh->Initialize(scene->mMeshes[0], program, {
			{ "world",  UniformType::MAT4,&boxObject->GetWorld()[0][0] }
		});
		boxObject->AddComponent(boxMesh.get());
		boxMesh->AddTexture("Assets/Textures/amazing.png");
		boxMesh->AddTexture("Assets/Textures/brick.jpg");
	}
}

void MultiTextureDemo::Shutdown()
{
}
