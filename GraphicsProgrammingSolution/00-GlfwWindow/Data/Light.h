#pragma once
#include <vec3.hpp>

struct PointLight
{
	glm::vec3 position;
	glm::vec3 color;
};

struct DirectionalLight
{
	glm::vec3 direction;
	glm::vec3 color;
};

struct SpotLight
{
	glm::vec3 color;
	glm::vec3 position;
	glm::vec3 direction;
	//angular attenuation exponent
	float exponent;
	//cut off angle between 0 and 90
	float cutOffAngle;
};