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

	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 512, 512);
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
	fboProgram.AddShaderFile(ShaderType::Vertex,"Assets/Shaders/Vertex/fbo.vert");
	fboProgram.AddShaderFile(ShaderType::Fragment,"Assets/Shaders/Fragment/fbo.frag");
	fboProgram.Build();

	textureProgram.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/texture.vert");
	textureProgram.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/texture.frag");
	textureProgram.Build();
	
	textureProgram.AddUniformBlock({ "TransformBlock", {
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
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


	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

	glGenTextures(1, &renderTargetTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTargetTexture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, 512, 512);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTargetTexture,0);

	glGenRenderbuffers(1, &depthBufferTexture);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferTexture);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);

	GLenum drawBufs[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBufs);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
		cubeMesh->AddTexture({ renderTargetTexture,GL_TEXTURE_2D, renderer->GetSampler(SamplerType::Linear).sampler });
	}

	auto monkeyScene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	monkey = std::unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 2.0f,0.0f,-2.0f });
	monkey->Update();
	if (monkeyScene && monkeyScene->HasMeshes())
	{
		monkeyMesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkey.get()));
		monkeyMesh->Initialize(monkeyScene->mMeshes[0], textureProgram, {
			{"world", UniformType::MAT4, &monkey->GetWorld()[0][0]}
		});
		monkeyMesh->AddTexture("Assets/Textures/brick.jpg");
	}

	importer.FreeScene();
}

void FrameBufferDemo::Shutdown()
{
}
