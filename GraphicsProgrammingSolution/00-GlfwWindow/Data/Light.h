#pragma once
#include <vec3.hpp>

struct PointLight
{
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;
};

struct DirectionalLight
{
	glm::vec3 direction;
	glm::vec3 color;
};