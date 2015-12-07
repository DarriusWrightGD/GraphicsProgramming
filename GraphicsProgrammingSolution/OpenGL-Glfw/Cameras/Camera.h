#pragma once
#include<vec3.hpp>
#include<mat4x4.hpp>
class Camera
{
public:
	Camera(float aspectRatio, float nearPlane = 0.1f, float farPlane = 1000.0f, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, -10.0f));
	Camera(float aspectRatio, glm::vec3 position, glm::vec3 lookAt);
	~Camera();
	
	void SetPosition(glm::vec3 position);
	void SetLookAt(glm::vec3 lookAt);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);
	void SetAspectRatio(float aspectRatio);
	void SetAspectRatio(float width, float height);
	void SetAspectRatio(int width, int height);
	void SetFOV(float degrees);

	glm::vec3 & GetPosition();
	glm::vec3 & GetLookAt();
	glm::vec3 & GetRight();
	glm::mat4 & GetView();
	glm::mat4 & GetProjection();

	void MoveLeft(float delta = FIXED_DELTA);
	void MoveRight(float delta = FIXED_DELTA);
	void MoveUp(float delta = FIXED_DELTA);
	void MoveDown(float delta = FIXED_DELTA);
	void MoveForward(float delta = FIXED_DELTA);
	void MoveBack(float delta = FIXED_DELTA);

protected:
	void UpdateProjection();
	void UpdateView();
	static const float FIXED_DELTA;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::vec3 direction;
	float fov;
	glm::vec3 position;
	float aspectRatio;
	glm::vec3 lookAt;
	float nearPlane;
	glm::vec3 right;
	float farPlane;
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
};

