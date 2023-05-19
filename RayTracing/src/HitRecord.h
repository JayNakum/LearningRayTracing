#ifndef HITRECORD_H
#define HITRECORD_H

#include "ray.h"
#include "vec3.h"
#include "Utility.h"

class Material;

struct HitRecord
{
	point3 p;
	vec3 normal;
	std::shared_ptr<Material> material;
	float t = 0.0f;
	bool frontFace = false;

	inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
	{
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

#endif // !HITRECORD_H
