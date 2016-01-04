#include "GuiComponent.h"
#include <GameObjects\GameObject.h>
#include <Util\ServiceLocator.h>
#include <Rendering\GLRenderer.h>

GuiComponent::GuiComponent(GameObject * gameObject, glm::vec4 offsets, float depth ) : DrawableComponent(gameObject),
offsets(offsets), depth(depth)
{
}

GuiComponent::GuiComponent(GameObject * gameObject, float left, float right, float top, float bottom, float depth) : DrawableComponent(gameObject),
offsets(left,right,top,bottom), depth(depth)
{
}

GuiComponent::GuiComponent(GameObject * gameObject, glm::vec2 start, glm::vec2 size,float depth) : DrawableComponent(gameObject),
depth(depth),offsets(start.x,start.x + size.x, start.y, start.y+size.y)
{

}

GuiComponent::~GuiComponent()
{
}

void GuiComponent::Update()
{
}

void GuiComponent::Draw()
{
}

void GuiComponent::Initialize(GLProgram & uiProgram)
{
	renderer = Services.Get<GLRenderer>();
	renderable = renderer->AddGuiRenderable(uiProgram, 
	{
		{ "offsets", UniformType::VEC4, &offsets[0] },
		{ "depth", UniformType::FLOAT, &depth},
	});
}

void GuiComponent::SetOffsets(glm::vec4 offsets) noexcept
{
	this->offsets = offsets;
}

void GuiComponent::SetOffsets(float left, float right, float top, float bottom) noexcept
{
	offsets = glm::vec4(left, right, top, bottom);
}

void GuiComponent::SetDepth(float depth) noexcept
{
	this->depth = depth;
}

TextureInfo GuiComponent::SetTexture(const char * fileName, SamplerType samplerType)
{
	return renderable->SetTexture(fileName, samplerType);
}

void GuiComponent::SetTexture(TextureInfo texture)
{
	renderable->SetTexture(texture);
}
