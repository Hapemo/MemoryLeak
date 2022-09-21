#pragma once
#include <pch.h>
#include <glm/glm.hpp>

struct Vertex
{
	Vertex() = default;
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoords;
	float texID;
};
