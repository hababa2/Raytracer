#pragma once
#include "Types.h"
#include "Ray.h"

class Material
{
public:
	virtual bool Scatter(const Ray& ray, const RaycastHit& hit, glm::vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const glm::vec3& albedo) : albedo{ albedo } {}
	virtual bool Scatter(const Ray& ray, const RaycastHit& hit, glm::vec3& attenuation, Ray& scattered) const override;

protected:
	glm::vec3 albedo;
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : albedo{ albedo }, fuzz{ fuzz } {}
	virtual bool Scatter(const Ray& ray, const RaycastHit& hit, glm::vec3& attenuation, Ray& scattered) const override;

protected:
	glm::vec3 albedo{ 0, 0, 0 };
	float fuzz = 0;
};
