#pragma once
#include <vector>
class Component;
/*Eventually move away from updating each gameobject 
for a more cache coherent solution of keeping all components 
in a single array that gets updated
*/
class GameObject
{
public:
	GameObject();
	~GameObject();
	void AddComponent(Component * component);
	void Update();
	void Draw();
private:
	std::vector<Component *> components;
};

