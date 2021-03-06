#pragma once
#include <Components\Component.h>
#include <mat4x4.hpp>
#include <mat3x3.hpp>
#include <vec3.hpp>
#include <Cameras\Camera.h>
class TransformComponent : public Component
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
	glm::mat4 & GetWorld() noexcept;
	glm::mat4 & GetNormal() noexcept;
	void WorldChanged()noexcept;
	void SetParent(TransformComponent * transform)noexcept;

	// Inherited via Component
	virtual void Update() override;
private:
	TransformComponent * parent;
	Camera * camera;
	glm::mat4 local;
	glm::mat4 world;
	glm::mat4 normal;
	glm::mat4 scale;
	glm::mat4 translation;
	glm::mat4 rotation;
	bool hasWorldChanged;
};

