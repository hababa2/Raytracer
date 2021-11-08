#include "Sphere.h"

bool Sphere::Hit(const Ray& r, float tMin, float tMax, RaycastHit& hit)
{
	glm::vec3 oc = r.origin - center;

	float a = glm::dot(r.direction, r.direction);
	float b = glm::dot(r.direction, oc) * 2;
	float c = glm::dot(oc, oc) - radius * radius;

    if (c > 0 && b > 0) return false;

	float disc = (b * b) - (4 * a * c);

    if (disc >= 0)
    {
        float s = sqrt(disc);
        float t = (-b - s) / (2 * a);

        if (t > tMin && t < tMax)
        {
            hit.t = t;
            hit.point = r.pointAt(hit.t);
            hit.material = material.get();
            hit.normal = (hit.point - center) / radius;
            hit.uv = GetSphericalUV(hit.normal);

            return true;
        }

        t = (-b + s) / (2 * a);

        if (t > tMin && t < tMax)
        {
            hit.t = t;
            hit.point = r.pointAt(hit.t);
            hit.material = material.get();
            hit.normal = (hit.point - center) / radius;
            return true;
        }
    }

    return false;
}
