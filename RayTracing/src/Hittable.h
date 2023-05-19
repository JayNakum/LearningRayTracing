#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "HitRecord.h"

class Hittable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, HitRecord& record) const = 0;
};

#endif // !HITTABLE_H
