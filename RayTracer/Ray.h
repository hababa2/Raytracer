#pragma once

#include "Types.h"

struct Ray
{
public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction) : origin{ origin }, direction{ direction } {}
	glm::vec3 pointAt(float t) const { return origin + direction * t; }
};

struct RaycastHit
{
	float t{ 0.0f };
	glm::vec3 point;
	glm::vec3 normal;
	class Material* material;
};