#include "ADSHalfwayVecDemo.h"



ADSHalfwayVecDemo::ADSHalfwayVecDemo()
{
}


ADSHalfwayVecDemo::~ADSHalfwayVecDemo()
{
}

void ADSHalfwayVecDemo::Update()
{
	sphere->Update();
}

void ADSHalfwayVecDemo::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->Render();
}

void ADSHalfwayVecDemo::OnResize(int width, int height)
{
	camera->SetAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	program.UpdateUniformBlock("TransformBlock");
}

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
void ADSHalfwayVecDemo::Initialize()
{
	glEnable(GL_DEPTH_TEST);

	light.position = glm::vec3(0.0, 0.0, -2.0f);
	light.color = glm::vec3(0.2f, 0.6f, 0.3f);

	program.AddShaderFile(ShaderType::Vertex, "Assets/Shaders/Vertex/halfwayVector.vert");
	program.AddShaderFile(ShaderType::Fragment, "Assets/Shaders/Fragment/halfwayVector.frag");
	program.Build();

	program.AddUniformBlock({ "TransformBlock",{
		{ "TransformBlock.view",&camera->GetView()[0][0],sizeof(camera->GetView()) },
		{"TransformBlock.projection",&camera->GetProjection()[0][0],sizeof(camera->GetProjection())},
		{"TransformBlock.eyePosition",&camera->GetPosition()[0], sizeof(camera->GetPosition())}
	} });

	program.AddUniformBlock({ "LightBlock", {
		{ "LightBlock.position",&light.position[0],sizeof(light.position) },
		{"LightBlock.color",&light.color[0],sizeof(light.color) }
	} });
	using std::unique_ptr;
	
	sphere = unique_ptr<GameObject>(new GameObject());
	sphere->GetTransform()->SetPosition({ 0.0f,0.0f,-5.0f });
	sphere->Update();

	Assimp::Importer importer;
	auto scene = importer.ReadFile("Assets/Models/Obj/sphere.obj", aiProcess_Triangulate);
	
	if (scene && scene->HasMeshes())
	{


		mesh = unique_ptr<MeshComponent>(new MeshComponent(sphere.get()));
		mesh->Initialize(scene->mMeshes[0], program, {
			{ "world", UniformType::MAT4, &sphere->GetWorld()[0][0] },
			{ "material.ambient", UniformType::VEC3, &mesh->GetMaterial().ambient[0] },
			{ "material.diffuse", UniformType::VEC3, &mesh->GetMaterial().diffuse[0] },
			{ "material.specular", UniformType::VEC4, &mesh->GetMaterial().specular[0] },
		});
		sphere->AddComponent(mesh.get());
		/*mesh->GetMaterial().ambient = glm::vec3(0.1f, 0.6f, 0.2f);
		mesh->GetMaterial().diffuse = glm::vec3(0.2f, 0.1f, 0.4f);
		mesh->GetMaterial().specular = glm::vec4(0.7f, 0.2f, 0.8f, 10.0f);*/
	}
	importer.FreeScene();

}

void ADSHalfwayVecDemo::Shutdown()
{
}
