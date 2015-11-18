#include "MeshComponent.h"
#include <GameObjects\GameObject.h>

/*There needs to be a clear separation where 
the mesh can be completely abstracted from from the renderer
therefore you should pull the data in only to forward it to a render layer with
the appropriate placements
*/

MeshComponent::MeshComponent(GameObject * gameObject, aiMesh * mesh) : DrawableComponent(gameObject)
{
}


MeshComponent::~MeshComponent()
{
}

void MeshComponent::Update()
{
}

void MeshComponent::Draw()
{
}
