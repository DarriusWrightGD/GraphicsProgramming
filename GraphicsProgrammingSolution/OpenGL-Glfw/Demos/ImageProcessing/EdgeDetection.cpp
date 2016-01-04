#include "EdgeDetection.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

EdgeDetection::EdgeDetection() : GlfwWindow(1920,1001, "Edge Detection")
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
	pass->Bind();
	//glViewport(0, 0, width, height);
	//camera->SetAspectRatio(width, height);
	renderer->RenderObjects();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, width, height);
	camera->SetAspectRatio(width, height);
	//renderer->Render();
	renderer->RenderFullScreen();
}

void EdgeDetection::OnResize(int w, int h)
{
	glViewport(0, 0, w, h);
	camera->SetAspectRatio(w, h);
	program.UpdateUniformBlock("TransformBlock");
}

void EdgeDetection::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/adsFrag.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/adsFrag.frag");
	program.Build();

	guiProgram.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/screenQuad.vert");
	guiProgram.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/screenQuad.frag");
	guiProgram.Build();

	edgeProgram.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/screenQuad.vert");
	edgeProgram.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/edgeDetect.frag");
	edgeProgram.Build();


	ui = std::unique_ptr<GameObject>(new GameObject());
	sampleRender = std::unique_ptr<GuiComponent>(new GuiComponent(ui.get(), glm::vec4(0, .5, 0, 1)));
	sampleRender->Initialize(guiProgram);

	pass = renderer->AddRenderPass({ width,height }, SamplerType::Linear);
	
	fullScreenRenderable = new FullScreenRenderable(edgeProgram, {	});
	fullScreenRenderable->SetTexture(pass->GetColorAttachment(0));
	renderer->SetFullScreenRenderable(fullScreenRenderable);
	//sampleRender->SetTexture(pass->GetDepthTexture());
	sampleRender->SetTexture(pass->GetColorAttachment(0));
	//sampleRender->SetTexture("Assets/Textures/add-sugar.png", SamplerType::Linear);
	
	light.color = glm::vec3(0.2f, 0.5f, 0.3f);
	light.position = glm::vec3(0.0f, 0.0f, 3.0f);
	program.AddUniformBlock({ "LightBlock",{
		{ "LightBlock.color", &light.color[0], sizeof(light.color) },
		{ "LightBlock.position", &light.position[0], sizeof(light.position) }
	} });

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0], sizeof(camera->GetView()) },
		{"TransformBlock.projection", &camera->GetProjection()[0][0], sizeof(camera->GetProjection())}
	} });

	monkey = std::unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f,-2.0f });
	monkey->Update();
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkey.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{ "world",UniformType::MAT4, &monkey->GetWorld()[0][0] },
			{ "normalMatrix",UniformType::MAT4, &monkey->GetTransform()->GetNormal()[0][0] },
			{ "material.ambient",UniformType::VEC3, &mesh->GetMaterial().ambient[0] },
			{ "material.diffuse",UniformType::VEC3, &mesh->GetMaterial().diffuse[0] },
			{ "material.specular",UniformType::VEC4, &mesh->GetMaterial().specular[0]},
		});
		monkey->AddComponent(mesh.get());
	}



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
}

void EdgeDetection::Shutdown()
{
}
