#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
public:
	ray() : m_time(0.0f) {}
	ray(const point3& origin, const vec3& direction, float time=0.0f)
		: m_origin(origin), m_direction(direction), m_time(time) {}

	inline point3 origin() const { return m_origin; }
	inline vec3 direction() const { return m_direction; }
	inline float time() const { return m_time; }

	inline point3 at(const float t) const
	{
		return m_origin + t * m_direction;
	}

private:
	point3 m_origin;
	vec3 m_direction;
	float m_time;
};

#endif // !RAY_H
