#include "vec3.h"

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat) 
{
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

vec3 random_in_unit_disk()
{
	while (true) {
		auto p = vec3(random_float(-1, 1), random_float(-1, 1), 0);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}
