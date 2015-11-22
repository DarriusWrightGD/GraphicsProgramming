#pragma once
#include <Components\Component.h>
#include <mat4x4.hpp>
#include <vec3.hpp>
class TransformComponent : Component
{
public:
	TransformComponent(GameObject * gameObject)noexcept;
	virtual ~TransformComponent()noexcept;
	void Translate(glm::vec3 translate) noexcept;
	void SetPosition(glm::vec3 position) noexcept;

	void Rotate(glm::vec3 rotate) noexcept;
	void SetRotation(glm::vec3 rotation) noexcept;

	void Scale(glm::vec3 scale) noexcept;
	void SetScale(glm::vec3 scale) noexcept;
	// Inherited via Component
	const glm::mat4 & GetWorld()const noexcept;
	virtual void Update() override;
	void WorldChanged()noexcept;
	void SetParent(TransformComponent * transform)noexcept;
private:
	TransformComponent * parent;
	glm::mat4 local;
	glm::mat4 world;
	glm::mat4 scale;
	glm::mat4 translation;
	glm::mat4 rotation;
	bool worldChanged;
};

