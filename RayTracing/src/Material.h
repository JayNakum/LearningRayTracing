#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"

#include "Utility.h"

struct HitRecord;

class Material
{
public:
	virtual bool scatter(
		const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered
	) const = 0;
};

class Lambertian : public Material
{
public:
	Lambertian(const color& a)
		: m_albedo(a) {}

	virtual bool scatter(
		const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered
	) const override;

private:
	color m_albedo;
};

class Metal : public Material
{
public:
	Metal(const color& a, const float fuzz = 0.0f)
		: m_albedo(a), m_fuzz(fuzz < 1 ? fuzz : 1) {}

	virtual bool scatter(
		const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered
	) const override;

private:
	color m_albedo;
	float m_fuzz;
};


class Dielectric : public Material
{
public:
	Dielectric(const float refractiveIndex)
		: m_refractiveIndex(refractiveIndex) {}

	virtual bool scatter(
		const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered
	) const override;

private:
	float m_refractiveIndex;
	static double reflectance(double cosine, double ref_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

#endif // !MATERIAL_H
