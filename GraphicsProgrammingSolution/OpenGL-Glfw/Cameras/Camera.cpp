#include "Camera.h"
#include <mat4x4.hpp>
#include <gtx\transform.hpp>

const float Camera::FIXED_DELTA = 1.0f / 3.0f;

Camera::Camera(float aspectRatio, float nearPlane, float farPlane, glm::vec3 position, glm::vec3 lookAt) : 
	aspectRatio(aspectRatio), nearPlane(nearPlane), position(position), lookAt(lookAt),farPlane(farPlane)
{

}
Camera::Camera(float aspectRatio, glm::vec3 position, glm::vec3 lookAt) : 
	Camera(aspectRatio,0.1f,100.0f,position,lookAt)
{

}
Camera::~Camera()
{

}


void Camera::SetPosition(glm::vec3 position) { this->position = position; UpdateView(); }
void Camera::SetLookAt(glm::vec3 lookAt) { this->lookAt = lookAt; UpdateView(); }
void Camera::SetNearPlane(float nearPlane) { this->nearPlane = nearPlane; UpdateProjection(); }
void Camera::SetFarPlane(float farPlane) { this->farPlane = farPlane; UpdateProjection(); }
void Camera::SetAspectRatio(float aspectRatio) { this->aspectRatio = aspectRatio; UpdateProjection(); }
void Camera::SetAspectRatio(float width, float height) { this->aspectRatio = width / height; UpdateProjection(); }
void Camera::SetFOV(float degrees) { this->fov = degrees; UpdateProjection(); }

glm::vec3 & Camera::GetPosition() { return position; }
glm::vec3 & Camera::GetLookAt() { return lookAt; }
glm::vec3 & Camera::GetRight() { return right; }
glm::mat4 & Camera::GetView() { return viewMatrix; }
glm::mat4 & Camera::GetProjection() { return projectionMatrix; }

void Camera::MoveLeft(float delta) { position.x -= delta; UpdateView(); }
void Camera::MoveRight(float delta ){ position.x += delta; UpdateView(); }
void Camera::MoveUp(float delta ){ position.y+= delta; UpdateView(); }
void Camera::MoveDown(float delta ){ position.y -= delta; UpdateView(); }
void Camera::MoveForward(float delta ){ position.z -= delta; UpdateView(); }
void Camera::MoveBack(float delta ){ position.z += delta; UpdateView(); }

void Camera::UpdateView()
{
	viewMatrix = glm::lookAt(position,lookAt,up);
}

void Camera::UpdateProjection()
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}