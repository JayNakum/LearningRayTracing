#pragma once

#include "ray.h"

struct HitRecord
{
	point3 p;
	vec3 normal;
	float t = 0.0f;
	bool frontFace = false;

	inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
	{
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, HitRecord& record) const = 0;
};
