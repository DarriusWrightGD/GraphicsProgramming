#include "FogDemo.h"



FogDemo::FogDemo()
{
}


FogDemo::~FogDemo()
{
}

void FogDemo::Update()
{
	monkey->Update();
}

void FogDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void FogDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

void FogDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/fog.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/fog.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock", {
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{"TransformBlock.eyePosition", &camera->GetPosition()[0], sizeof(camera->GetPosition())},
	}});

	float minDist = 0.0f;
	float maxDist = 5.5f;
	glm::vec3 color(0.3f, 0.3f, 0.3f);
	glClearColor(color.x, color.y, color.z, 1.0f);
	program.AddUniformBlock({ "FogBlock",{
		{ "FogBlock.minDist", &minDist, sizeof(minDist) },
		{ "FogBlock.maxDist", &maxDist, sizeof(maxDist) },
		{"FogBlock.color", &color[0], sizeof(color)},
	} });

	monkey = std::unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	monkey->Update();
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);

	if (scene && scene->HasMeshes())
	{
		mesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkey.get(), scene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform("world", { UniformType::MAT4, &monkey->GetWorld()[0][0] });
		}));
	}

}

void FogDemo::Shutdown()
{
}
