#pragma once

#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere() : m_center{0.0f, 0.0f, 0.0f}, m_radius(0.0f) {}
	Sphere(point3 center, float radius) : m_center(center), m_radius(radius) {}

	virtual bool hit(const ray& r, float t_min, float t_max, HitRecord& record) const override;

private:
	point3 m_center;
	float m_radius;
};