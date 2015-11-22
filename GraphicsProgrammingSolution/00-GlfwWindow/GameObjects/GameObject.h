#pragma once
#include <vector>
class Component;
class TransformComponent;
/*Eventually move away from updating each gameobject 
for a more cache coherent solution of keeping all components 
in a single array that gets updated
*/
class GameObject
{
public:
	GameObject(GameObject * parent = nullptr);
	~GameObject();
	void AddComponent(Component * component);
	void AddChild(GameObject * gameObject);
	void SetParent(GameObject * parent);
	const std::vector<GameObject *> & GetChildren();
	void Update();
	void Draw();
	TransformComponent * GetTransform();
private:
	std::vector<Component *> components;
	TransformComponent * transform;
	GameObject * parent;
	std::vector<GameObject *> children;
};

