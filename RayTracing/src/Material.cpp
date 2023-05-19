#include "Material.h"

#include "Utility.h"
#include "HitRecord.h"

bool Lambertian::scatter(const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered) const
{
	auto scatter_direction = record.normal + random_unit_vector();
	if (scatter_direction.near_zero())
		scatter_direction = record.normal;
	scattered = ray(record.p, scatter_direction);
	attenuation = m_albedo;
	return true;
}

bool Metal::scatter(const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered) const
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), record.normal);
	scattered = ray(record.p, reflected + m_fuzz * random_in_unit_sphere());
	attenuation = m_albedo;
	return (dot(scattered.direction(), record.normal) > 0);
}

bool Dielectric::scatter(const ray& r_in, const HitRecord& record, color& attenuation, ray& scattered) const
{
	attenuation = color(1.0f, 1.0f, 1.0f);
	float refractionRatio = record.frontFace ? (1.0f / m_refractiveIndex) : m_refractiveIndex;

	vec3 unit_direction = unit_vector(r_in.direction());
	double cos_theta = fmin(dot(-unit_direction, record.normal), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refract = refractionRatio * sin_theta > 1.0;
	vec3 direction;

	if (cannot_refract || reflectance(cos_theta, refractionRatio) > random_float())
		direction = reflect(unit_direction, record.normal);
	else
		direction = refract(unit_direction, record.normal, refractionRatio);

	scattered = ray(record.p, direction);

	return true;
}
