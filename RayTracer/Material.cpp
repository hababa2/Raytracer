#include "Material.h"

bool Lambertian::Scatter(const Ray& ray, const RaycastHit& hit, glm::vec3& attenuation, Ray& scattered) const
{
    glm::vec3 dir = glm::normalize(hit.normal + randomInUnitSphere());

    scattered = { hit.point, dir };
    attenuation = albedo;

    return true;
}

bool Metal::Scatter(const Ray& ray, const RaycastHit& hit, glm::vec3& attenuation, Ray& scattered) const
{
    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    scattered = { hit.point, reflected + (randomInUnitSphere() * fuzz) };
    attenuation = albedo;

    return glm::dot(scattered.direction, hit.normal) > 0;
}
