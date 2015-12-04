#pragma once
class GameObject;
class Component
{
public:
	Component(GameObject * gameObject);
	~Component();

	virtual void Update() = 0;
protected:
	GameObject * gameObject;
};

