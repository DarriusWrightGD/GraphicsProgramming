#include "Texture2DDemo.h"
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <OGLC\GLProgram.h>
#include <SOIL.h>

Texture2DDemo::Texture2DDemo()
{
}


Texture2DDemo::~Texture2DDemo()
{
}

void Texture2DDemo::Update()
{
	boxObject->Update();
}

void Texture2DDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void Texture2DDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}
void Texture2DDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/texture.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/texture.frag");
	program.Build();



	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view",&camera->GetView()[0][0], sizeof(camera->GetView()) },
		{ "TransformBlock.projection",&camera->GetProjection()[0][0], sizeof(camera->GetProjection()) },
	} });

	using std::unique_ptr;
	boxObject = unique_ptr<GameObject>(new GameObject());
	Assimp::Importer importer;
	boxObject->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	boxObject->Update();
	auto scene = importer.ReadFile("Assets/Models/Obj/box.obj", aiProcess_Triangulate);

	if (scene && scene->HasMeshes())
	{
		boxMesh = unique_ptr<MeshComponent>(new MeshComponent(boxObject.get(), scene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform("world", { UniformType::MAT4,&boxObject->GetWorld()[0][0] });
		}));
		boxObject->AddComponent(boxMesh.get());
	}

	auto width = 0, height = 0, channels = 0;
	auto imageBytes = SOIL_load_image("Assets/Textures/brick.jpg", &width, &height, &channels, SOIL_LOAD_RGB);
	program.Use();
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexStorage2D(GL_TEXTURE_2D, 1, (channels == 3) ? GL_RGB8 : GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, (channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, imageBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete[] imageBytes;

	auto textureLocation = glGetUniformLocation(program.GetHandle(), "texture1");
	if (textureLocation >= 0)
		glUniform1i(textureLocation, 0);
}

void Texture2DDemo::Shutdown()
{
}
