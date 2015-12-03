#include "AlphaMapDemo.h"



AlphaMapDemo::AlphaMapDemo()
{
}


AlphaMapDemo::~AlphaMapDemo()
{
}

void AlphaMapDemo::Update()
{
	box->Update();
}

void AlphaMapDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void AlphaMapDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\postprocess.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>

void AlphaMapDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.7f, 0.2f, 1.0f);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/alphamap.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/alphamap.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock", {
		{ "TransformBlock.view",&camera->GetView()[0][0],sizeof(camera->GetView()) },
		{"TransformBlock.projection",&camera->GetProjection()[0][0],sizeof(camera->GetProjection()) },
	} });
	
	using std::unique_ptr;

	box = unique_ptr<GameObject>(new GameObject());
	box->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	box->Update();
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);

	if (scene && scene->HasMeshes())
	{
		mesh = unique_ptr<MeshComponent>(new MeshComponent(box.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{"world",UniformType::MAT4, &box->GetWorld()[0][0]}
		});
		mesh->AddTexture("Assets/Textures/amazing.png");
		//mesh->AddTexture("Assets/Textures/brick.jpg");

		box->AddComponent(mesh.get());
	}
}

void AlphaMapDemo::Shutdown()
{
}
