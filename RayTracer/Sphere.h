#pragma once

#include "Geometry.h"

class Sphere : public Geometry
{
public:
    Sphere() = default;
    Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
        Geometry{ material },
        center{ center },
        radius{ radius } {}

    bool Hit(const Ray & r, float tMin, float tMax, RaycastHit & hit) override;

public:
    glm::vec3 center;
    float radius{ 0.0f };
};