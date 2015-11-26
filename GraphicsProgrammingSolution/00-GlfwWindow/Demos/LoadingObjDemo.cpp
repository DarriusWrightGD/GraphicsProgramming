#include "LoadingObjDemo.h"
#include <Util\ServiceLocator.h>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <gtc/constants.hpp>
#include <Components\TransformComponent.h>

#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <Data\Vertex.h>

LoadingObjDemo::LoadingObjDemo()
{
}


LoadingObjDemo::~LoadingObjDemo()
{
}

void LoadingObjDemo::Update()
{
	gameObject->GetTransform()->Rotate(glm::vec3(0.1f, 0.1f, 0.0f));
	gameObject->Update();
}

void LoadingObjDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}
void LoadingObjDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.4f, 0.7f, 0.2f, 1.0f);
	PrintUniformInfo();

	program.Initialize();
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/uniforms.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/uniforms.frag");
	program.Build();

	input->addBinding(GLFW_KEY_LEFT, [this](InputInfo info){
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
	
	UniformBufferBlock uniformBufferBlock("TransformBlock", {
		{ "TransformBlock.projection",&camera->GetProjection()[0][0],sizeof(mat4) },
		{ "TransformBlock.view",&camera->GetView()[0][0],sizeof(mat4) },
	});

	program.AddUniformBlock(uniformBufferBlock);
	InitializeObj("Assets/Models/Obj/monkey.obj");
	OnResize(width, height);
}

void LoadingObjDemo::PrintUniformInfo()
{
	GLint max;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &max);
	cout << "Vertex Uniforms : " << max << endl;
	glGetIntegerv(GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, &max);
	cout << "Tessellation Uniforms : " << max << endl;
	glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &max);
	cout << "Geometry Uniforms : " << max << endl;
	glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &max);
	cout << "Fragment Uniforms : " << max << endl;

	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max);
	cout << "\nMax Uniform Block Size : " << max << endl;
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &max);
	cout << "\nMax Uniform Block Bindings : " << max << endl;

}
void LoadingObjDemo::OnResize(int w, int h)
{
	glViewport(0, 0, w, h);
	aspectRatio = (float)w / h;
	camera->SetAspectRatio(aspectRatio);
	program.UpdateUniformBlock("TransformBlock");
}

void LoadingObjDemo::InitializeObj(string filePath)
{
	Assimp::Importer importer;
	auto scene = importer.ReadFile(filePath.c_str(),
		aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs );
	if (scene)
	{
		auto mesh = scene->mMeshes[0];
		gameObject = std::unique_ptr<GameObject>(new GameObject());
		meshComponent = std::unique_ptr<MeshComponent>(new MeshComponent(gameObject.get(), mesh, program, [this](GLProgram & progran) {
			program.UpdateUniform(program.GetUniformLocation("model"), { UniformType::MAT4,&gameObject->GetWorld()[0][0] });
		}));
		gameObject->GetTransform()->SetPosition(glm::vec3(0, 0, -10));
		//program.AddUniform("model", , UniformType::MAT4);
	}
}

void LoadingObjDemo::Shutdown()
{
}
