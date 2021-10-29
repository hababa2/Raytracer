#pragma once
#include "Geometry.h"

class Plane : public Geometry
{
public:
	Plane() = default;
	Plane(const glm::vec3& center, const glm::vec3& normal, std::shared_ptr<Material> material) : center{ center }, normal{ normal }, Geometry{ material } { }

	bool Hit(const Ray & r, float tMin, float tMax, RaycastHit & hit) override;

public:
	glm::vec3 center{ 0, 0, 0 };
	glm::vec3 normal{ 0, 0, 0 };
};