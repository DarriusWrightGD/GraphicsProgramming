#pragma once
#include <Components\Component.h>
class DrawableComponent : public Component
{
public:
	DrawableComponent(GameObject * gameObject);
	virtual ~DrawableComponent();
	virtual void Draw() = 0;
};

