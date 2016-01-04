#include "FrameBufferDemo.h"



FrameBufferDemo::FrameBufferDemo()
{
}


FrameBufferDemo::~FrameBufferDemo()
{
}

void FrameBufferDemo::Update()
{
}

void FrameBufferDemo::Render()
{
	/*
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 512, 512);*/
	renderPass->Bind();
	camera->SetAspectRatio(512, 512);
	renderer->Render(monkeyMesh->GetRenderable());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);
	camera->SetAspectRatio(width, height);
	renderer->Render(cubeMesh->GetRenderable());
}

void FrameBufferDemo::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetAspectRatio(width, height);
	fboProgram.UpdateUniformBlock("TransformBlock");
	textureProgram.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>

void FrameBufferDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	fboProgram.AddShaderFile(ShaderType::Vertex,"Assets/Shaders/Vertex/fbo.vert");
	fboProgram.AddShaderFile(ShaderType::Fragment,"Assets/Shaders/Fragment/fbo.frag");
	fboProgram.Build();

	textureProgram.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/adsFrag.vert");
	textureProgram.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/adsFrag.frag");
	textureProgram.Build();
	
	textureProgram.AddUniformBlock({ "TransformBlock", {
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
	} });

	light.color = glm::vec3(0.2f, 0.5f, 0.3f);
	light.position = glm::vec3(0.0f, 0.0f, 3.0f);

	textureProgram.AddUniformBlock({ "LightBlock",{
		{ "LightBlock.color", &light.color[0], sizeof(light.color) },
		{ "LightBlock.position", &light.position[0], sizeof(light.position) }
	} });

	fboProgram.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
	} });


	input->addBinding(GLFW_KEY_LEFT, [this](InputInfo info) {
		camera->MoveLeft();
		fboProgram.UpdateUniformBlock("TransformBlock");
		textureProgram.UpdateUniformBlock("TransformBlock");
	});

	input->addBinding(GLFW_KEY_RIGHT, [this](InputInfo info) {
		camera->MoveRight();
		fboProgram.UpdateUniformBlock("TransformBlock");
		textureProgram.UpdateUniformBlock("TransformBlock");
	});


	input->addBinding(GLFW_KEY_UP, [this](InputInfo info) {
		camera->MoveForward();
		textureProgram.UpdateUniformBlock("TransformBlock");
		fboProgram.UpdateUniformBlock("TransformBlock");
	});

	input->addBinding(GLFW_KEY_DOWN, [this](InputInfo info) {
		camera->MoveBack();
		textureProgram.UpdateUniformBlock("TransformBlock");
		fboProgram.UpdateUniformBlock("TransformBlock");
	});

	renderPass = renderer->AddRenderPass({512,512},SamplerType::Linear);

	Assimp::Importer importer;
	auto cubeScene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);
	cube = std::unique_ptr<GameObject>(new GameObject());
	cube->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	cube->GetTransform()->SetScale({ 20.0f,20.0f,20.0f });
	cube->Update();
	if (cubeScene && cubeScene->HasMeshes())
	{
		cubeMesh = std::unique_ptr<MeshComponent>(new MeshComponent(cube.get()));
		cubeMesh->Initialize(cubeScene->mMeshes[0], fboProgram, {
			{"world", UniformType::MAT4, &cube->GetWorld()[0][0]},
		});
		cubeMesh->AddTexture(renderPass->GetColorAttachment(0));
	}

	auto monkeyScene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	monkey = std::unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 2.0f,0.0f,-2.0f });
	monkey->Update();
	if (monkeyScene && monkeyScene->HasMeshes())
	{
		monkeyMesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkey.get()));
		monkeyMesh->Initialize(monkeyScene->mMeshes[0], textureProgram, {
			{"world", UniformType::MAT4, &monkey->GetWorld()[0][0]},
			{ "normalMatrix",UniformType::MAT4, &monkey->GetTransform()->GetNormal()[0][0] },

		{ "material.ambient",UniformType::VEC3, &monkeyMesh->GetMaterial().ambient[0] },
		{ "material.diffuse",UniformType::VEC3, &monkeyMesh->GetMaterial().diffuse[0] },
		{ "material.specular",UniformType::VEC4, &monkeyMesh->GetMaterial().specular[0] },

		});
		//monkeyMesh->AddTexture("Assets/Textures/brick.jpg");
	}

	importer.FreeScene();
}

void FrameBufferDemo::Shutdown()
{
}
