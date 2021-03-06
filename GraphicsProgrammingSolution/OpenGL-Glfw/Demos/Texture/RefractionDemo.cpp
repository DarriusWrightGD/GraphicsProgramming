#include "RefractionDemo.h"
#include <assimp\postprocess.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>

RefractionDemo::RefractionDemo()
{
}


RefractionDemo::~RefractionDemo()
{
}


void RefractionDemo::Update()
{
	skyBox->Update();
	box->Update();
}

void RefractionDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void RefractionDemo::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetAspectRatio(static_cast<float>(width), static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

void RefractionDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/refraction.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/refraction.frag");
	program.Build();


	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
		{ "TransformBlock.eyePosition", &camera->GetPosition()[0], sizeof(camera->GetPosition()) },
	} });


	box = std::unique_ptr<GameObject>(new GameObject());
	box->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	box->GetTransform()->SetScale({ 1.0f,1.0f,1.0f });

	box->Update();


	skyBox = std::unique_ptr<GameObject>(new GameObject());
	skyBox->GetTransform()->SetScale({ 50.0f,50.0f,50.0f });

	skyBox->Update();

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

	Assimp::Importer import;
	auto scene = import.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = std::unique_ptr<MeshComponent>(new MeshComponent(box.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{ "world", UniformType::MAT4, &box->GetWorld()[0][0] },
			{ "drawSkyBox", UniformType::BOOL,&objectDraw },
			{ "material.reflectionFactor", UniformType::FLOAT, &refraction },
			{"material.eta", UniformType::FLOAT, &eta}
		});
		box->AddComponent(mesh.get());

		

		skyBoxMesh = std::unique_ptr<MeshComponent>(new MeshComponent(skyBox.get()));
		skyBoxMesh->Initialize(scene->mMeshes[0], program, {
			{ "world", UniformType::MAT4, &skyBox->GetWorld()[0][0] },
			{ "drawSkyBox", UniformType::BOOL,&skyBoxDraw },
		});

		skyBox->AddComponent(skyBoxMesh.get());
		skyBoxMesh->AddTexture(mesh->AddCubeMap("Assets/Textures/Cubemaps/Storforse", "jpg"));

		import.FreeScene();
	}
}

void RefractionDemo::Shutdown()
{
}