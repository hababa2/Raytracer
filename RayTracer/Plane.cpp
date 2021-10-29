#include "Plane.h"

bool Plane::Hit(const Ray& r, float tMin, float tMax, RaycastHit& hit)
{
	float denominator = glm::dot(r.direction, normal);

	if (abs(denominator) < glm::epsilon<float>())
	{
		return false;
	}

	float t = glm::dot(center - r.origin, normal) / denominator;

	if (t < 0)
	{
		return false;
	}

	if (t >= tMin && t <= tMax)
	{
		hit.t = t;
		hit.point = r.pointAt(t);
		hit.material = material.get();
		hit.normal = normal;

		return true;
	}

	return false;
}
