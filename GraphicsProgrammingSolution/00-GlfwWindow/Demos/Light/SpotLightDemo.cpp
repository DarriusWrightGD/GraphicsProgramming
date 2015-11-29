#include "SpotLightDemo.h"



SpotLightDemo::SpotLightDemo()
{
}


SpotLightDemo::~SpotLightDemo()
{
}

void SpotLightDemo::Update()
{
	monkey->Update();
}

void SpotLightDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void SpotLightDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <glm.hpp>
void SpotLightDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/spotlight.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/spotlight.frag");
	program.Build();

	using std::unique_ptr;
	monkey = std::unique_ptr<GameObject>(new GameObject());
	monkey->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	monkey->Update();
	light.color = glm::vec3(0.4f, 0.5f, 0.7f);
	light.position = glm::vec3(2.0f, 0.0f, -1.0f);
	light.direction = glm::normalize( glm::vec3(0.0f, 0.0f, -5.0f ) - light.position);
	light.cutOffAngle = 12.0f;
	light.exponent = 5.0f;

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view", &camera->GetView()[0][0],sizeof(camera->GetView()) },
		{ "TransformBlock.projection", &camera->GetProjection()[0][0],sizeof(camera->GetProjection()) },
		{"TransformBlock.eyePosition", &camera->GetPosition()[0],sizeof(camera->GetPosition())},
	} });

	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.color", &light.color.x,sizeof(light.color) },
		{ "LightBlock.position", &light.position.x,sizeof(light.position) },
		{ "LightBlock.direction", &light.direction.x,sizeof(light.direction) },
		{ "LightBlock.exponent", &light.exponent,sizeof(light.exponent) },
		{ "LightBlock.cutOffAngle", &light.cutOffAngle,sizeof(light.cutOffAngle) },
	} });
	
	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/monkey.obj", aiProcess_Triangulate);
	if (scene && scene->HasMeshes())
	{
		mesh = std::unique_ptr<MeshComponent>(new MeshComponent(monkey.get(), scene->mMeshes[0], program, [this](GLProgram & program) {
			program.UpdateUniform("world", { UniformType::MAT4,&monkey->GetWorld()[0][0] });
			program.UpdateUniform("material.ambient", { UniformType::VEC3, &mesh->GetMaterial().ambient[0] });
			program.UpdateUniform("material.diffuse", { UniformType::VEC3, &mesh->GetMaterial().diffuse[0] });
			program.UpdateUniform("material.specular", { UniformType::VEC4, &mesh->GetMaterial().specular[0] });
		}));

		monkey->AddComponent(mesh.get());
		mesh->GetMaterial().ambient = glm::vec3(0.2f, 0.4f, 0.7f);
		mesh->GetMaterial().diffuse = glm::vec3(0.8f, 0.1f, 0.1f);
		mesh->GetMaterial().specular = glm::vec4(0.3f, 0.7f, 0.3f,10.0f);
	}

	
}

void SpotLightDemo::Shutdown()
{
}
