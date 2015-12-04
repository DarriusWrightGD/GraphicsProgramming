#include "TransformComponent.h"
#include <gtx\transform.hpp>
#include <GameObjects\GameObject.h>

TransformComponent::TransformComponent(GameObject * gameObject)noexcept : Component(gameObject), parent(nullptr), scale(glm::scale(glm::vec3(1.0f,1.0f,1.0f)))
{
}


TransformComponent::~TransformComponent() noexcept
{
}

void TransformComponent::SetParent(TransformComponent * transform)noexcept
{
	parent = transform;
}

void TransformComponent::WorldChanged() noexcept
{
	worldChanged = true;
}

void TransformComponent::Update()
{
	if (worldChanged)
	{
		local = translation * rotation * scale;
		world = (parent == nullptr) ? local : local * parent->GetWorld();
		for (auto child : gameObject->GetChildren())
		{
			child->GetTransform()->WorldChanged();
		}
		worldChanged = false;
	}
}

glm::mat4 & TransformComponent::GetWorld() noexcept
{
	return world;
}

void TransformComponent::Translate(glm::vec3 translate) noexcept
{
	translation *= glm::translate(translate);
	WorldChanged();
}
void TransformComponent::SetPosition(glm::vec3 position) noexcept
{
	translation = glm::translate(position);
	WorldChanged();
}

void TransformComponent::Rotate(glm::vec3 rotate) noexcept
{
	rotation *= (glm::rotate(rotate.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
	glm::rotate(rotate.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
	glm::rotate(rotate.z,glm::vec3(0.0f,0.0f,1.0f)));
	WorldChanged();
}
void TransformComponent::SetRotation(glm::vec3 rotation) noexcept
{
	this->rotation = (glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)));
	WorldChanged();
}

void TransformComponent::Scale(glm::vec3 scale) noexcept
{
	this->scale *= (glm::scale(scale));
	WorldChanged();
}
void TransformComponent::SetScale(glm::vec3 scale) noexcept
{
	this->scale = glm::scale(scale);
	WorldChanged();
}
