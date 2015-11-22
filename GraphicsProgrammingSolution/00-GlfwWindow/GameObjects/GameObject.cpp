#include "GameObject.h"
#include <Components\Component.h>
#include <Components\DrawableComponent.h>
#include <Components\TransformComponent.h>
GameObject::GameObject(GameObject * parent) : parent(parent)
{
	transform = std::unique_ptr<TransformComponent>(new TransformComponent(this));
	SetParent(parent);
	AddComponent(transform.get());
}


GameObject::~GameObject()
{
}

glm::mat4 & GameObject::GetWorld() noexcept
{
	return transform->GetWorld();
}

void GameObject::AddComponent(Component * component)
{
	components.push_back(component);
}

void GameObject::Draw()
{
	for (auto component : components)
	{
		if (auto drawableComponent = dynamic_cast<DrawableComponent *>(component))
		{
			drawableComponent->Draw();
		}
	}
}

void GameObject::AddChild(GameObject * gameObject)
{
	children.push_back(gameObject);
}
void GameObject::SetParent(GameObject * parent)
{
	this->parent = parent;
	transform->SetParent((parent == nullptr) ? nullptr : parent->GetTransform());
}
const std::vector<GameObject *> & GameObject::GetChildren()
{
	return children;
}

TransformComponent * GameObject::GetTransform()
{
	return transform.get();
}

void GameObject::Update()
{
	for (auto component : components)
	{
		component->Update();
	}
}
