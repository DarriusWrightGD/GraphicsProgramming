#include "ProjectedTextureDemo.h"



ProjectedTextureDemo::ProjectedTextureDemo()
{
}


ProjectedTextureDemo::~ProjectedTextureDemo()
{
}

void ProjectedTextureDemo::Update()
{
	plane->Update();
	cube->Update();
}

void ProjectedTextureDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void ProjectedTextureDemo::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetAspectRatio(width, height);
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <gtx\transform.hpp>

void ProjectedTextureDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	program.AddShaderFile(ShaderType::Vertex,"Assets/Shaders/Vertex/projectedTexture.vert");
	program.AddShaderFile(ShaderType::Fragment,"Assets/Shaders/Fragment/projectedTexture.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock", {
		{ "TransformBlock.view",&camera->GetView()[0][0], sizeof(camera->GetView()) },
		{"TransformBlock.projection",&camera->GetProjection()[0][0], sizeof(camera->GetProjection())},
		{"TransformBlock.eyePosition", &camera->GetPosition()[0], sizeof(camera->GetPosition())}
	}});


	light.position = glm::vec3(6.0f, 0.0f, 0.0f);
	light.color = glm::vec3(0.5f, 0.7f, 0.1f);


	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.position", &light.position[0], sizeof(light.position) },
		{"LightBlock.color", &light.color[0], sizeof(light.color)},
	} });

	glm::vec3 projectorPosition(0.0f);
	glm::vec3 projectorLookAt( 1.0f,1.0f,-3.0f );
	glm::vec3 up(0.0f,1.0f,0.0f);

	glm::mat4 view = glm::lookAt(projectorPosition, projectorLookAt, up);
	glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.2f, 1000.0f);

	projectorMatrix = glm::translate(glm::vec3(0.5f)) * glm::scale(glm::vec3(0.5f)) * 
		projection * view;
	program.AddUniform("projectorMatrix", &projectorMatrix[0][0], UniformType::MAT4);
	
	using std::unique_ptr;

	plane = std::unique_ptr<GameObject>(new GameObject());
	plane->GetTransform()->SetPosition({ 0.0f,-1.0f,-5.0f });
	plane->GetTransform()->SetScale({ 50.0f,1.0f,50.0f });
	plane->GetTransform()->SetRotation({ 40.0f,0.0f,0.0f });
	cube = std::unique_ptr<GameObject>(new GameObject());
	cube->GetTransform()->SetPosition({ 0.0f,0.0f,-3.0f });

	Assimp::Importer importer;
	auto planeScene = importer.ReadFile("Assets/Models/Obj/plane.obj", aiProcess_Triangulate);
	TextureInfo texture;
	if (planeScene && planeScene->HasMeshes())
	{
		planeMesh = unique_ptr<MeshComponent>(new MeshComponent(plane.get()));
		planeMesh->Initialize(planeScene->mMeshes[0], program, {
			{"world", UniformType::MAT4, &plane->GetWorld()[0][0]},
			{"normalMatrix", UniformType::MAT4, &plane->GetTransform()->GetNormal()[0][0]},
			{"material.diffuse", UniformType::VEC3, &planeMesh->GetMaterial().diffuse[0]}
		});
		texture = planeMesh->AddTexture("Assets/Textures/amazing.png", TextureWrapType::Projection);
		plane->AddComponent(planeMesh.get());
	}
	importer.FreeScene();


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
	
	auto cubeScene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);
	if (cubeScene && cubeScene->HasMeshes())
	{
		cubeMesh = unique_ptr<MeshComponent>(new MeshComponent(cube.get()));
		cubeMesh->Initialize(cubeScene->mMeshes[0], program, {
			{"world", UniformType::MAT4, &cube->GetWorld()[0][0]},
			{"normalMatrix", UniformType::MAT4, &cube->GetTransform()->GetNormal()[0][0]},
			{"material.diffuse", UniformType::VEC3, &cubeMesh->GetMaterial().diffuse[0]}
		});

		cubeMesh->AddTexture(texture);
		cube->AddComponent(cubeMesh.get());
	}
	importer.FreeScene();
}

void ProjectedTextureDemo::Shutdown()
{
}

