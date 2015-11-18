#include "GameObject.h"
#include <Components\Component.h>
#include <Components\DrawableComponent.h>

GameObject::GameObject()
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

void GameObject::Update()
{
	for (auto component : components)
	{
		component->Update();
	}
}
