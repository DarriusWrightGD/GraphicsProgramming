#include "Component.h"
#include <GameObjects\GameObject.h>


Component::Component(GameObject * gameObject) : gameObject(gameObject)
{
}


Component::~Component()
{
}
