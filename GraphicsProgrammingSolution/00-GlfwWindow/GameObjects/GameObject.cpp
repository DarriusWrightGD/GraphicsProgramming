#include "GameObject.h"
#include <Components\Component.h>
#include <Components\DrawableComponent.h>

GameObject::GameObject(GameObject * parent) : parent(parent)
{
}


GameObject::~GameObject()
{
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
}
const std::vector<GameObject *> & GameObject::GetChildren()
{
	return children;
}

TransformComponent * GameObject::GetTransform()
{
	return transform;
}

void GameObject::Update()
{
	for (auto component : components)
	{
		component->Update();
	}
}
