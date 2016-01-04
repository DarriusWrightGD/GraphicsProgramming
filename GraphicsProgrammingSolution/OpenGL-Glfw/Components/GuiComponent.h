#pragma once
#include <Components/DrawableComponent.h>
#include <OGLC/GLProgram.h>
#include <vec4.hpp>
#include <vec2.hpp>
#include <Cameras\Camera.h>
#include <Rendering\GuiRenderable.h>

class GameObject;
class GuiComponent : public DrawableComponent
{
public:
	/*The offsets go in the following order: left, right, top, bottom*/
	GuiComponent(GameObject * gameObject, glm::vec4 offsets = glm::vec4(0,1,0,1), float depth = 0.1f);
	GuiComponent(GameObject * gameObject, float left, float right, float top, float bottom, float depth = 0.1f);
	GuiComponent(GameObject * gameObject, glm::vec2 start, glm::vec2 size, float depth = 0.1f);
	~GuiComponent();
	virtual void Update() override;
	virtual void Draw() override;
	void Initialize(GLProgram & uiProgram);
	void SetOffsets(glm::vec4 offsets) noexcept;
	void SetOffsets(float left, float right, float top, float bottom) noexcept;
	void SetDepth(float depth) noexcept;
	TextureInfo SetTexture(const char * fileName, SamplerType samplerType);
	void SetTexture(TextureInfo texture);
private:
	GuiRenderable * renderable;
	GLRenderer * renderer;
	Camera * camera;
	glm::vec4 offsets;
	float depth;
};

