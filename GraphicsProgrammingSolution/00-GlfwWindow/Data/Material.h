#pragma once
#include <vec3.hpp>
#include <vec4.hpp>
struct Material
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec4 specular;
};