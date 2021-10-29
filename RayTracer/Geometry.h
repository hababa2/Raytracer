#pragma once
#include "Material.h"
#include <memory>

class Geometry
{
public:
    Geometry() = default;
    Geometry(std::shared_ptr<Material> material) : material{ material } {}
    virtual ~Geometry() = default;

    virtual bool Hit(const Ray& r, float tMin, float tMax, RaycastHit& hit) = 0;

public:
    std::shared_ptr<Material> material;
};