#include "EdgeDetection.h"



EdgeDetection::EdgeDetection()
{
}


EdgeDetection::~EdgeDetection()
{
}

void EdgeDetection::Update()
{
	monkey->Update();
}

void EdgeDetection::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
	guiProgram.Use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void EdgeDetection::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetAspectRatio(width, height);
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

void EdgeDetection::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/edgeDetect.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/edgeDetect.frag");
	program.Build();

	guiProgram.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/screenQuad.vert");
	guiProgram.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/screenQuad.frag");
	guiProgram.Build();


	pass = renderer->AddRenderPass({ width,height }, SamplerType::Nearest);

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{"TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection())}
	} });

	monkey = std::unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f,-2.0f });
	
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkey.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{"world",UniformType::MAT4, &monkey->GetWorld()[0][0]}
		});
		monkey->AddComponent(mesh.get());
	}
}

void EdgeDetection::Shutdown()
{
}
