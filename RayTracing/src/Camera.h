#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec3.h"

class Camera
{
public:
	Camera(
		point3 lookFrom,
		point3 lookAt,
		vec3 vUp,
		float vfov,
		float aspectRatio,
		float aperture,
		float focusDist
	)
	{
		float theta = degrees_to_radians(vfov);
		float h = tan(theta / 2);
		float viewportHeight = 2.0f * h;
		float viewportWidth = aspectRatio * viewportHeight;

		w = unit_vector(lookFrom - lookAt);
		u = unit_vector(cross(vUp, w));
		v = cross(w, u);

		m_origin = lookFrom;
		m_horizontal = focusDist * viewportWidth * u;
		m_vertical = focusDist * viewportHeight * v;
		m_lowerLeftCorner = m_origin - m_horizontal / 2 - m_vertical / 2 - focusDist * w;

		lensRadius = aperture / 2;
	}

	ray getRay(float s, float t)
	{
		vec3 rd = lensRadius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(
			m_origin + offset, 
			m_lowerLeftCorner + s * m_horizontal + t * m_vertical - m_origin - offset
		);
	}

private:
	point3 m_origin;
	point3 m_lowerLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 u, v, w;
	double lensRadius;
};

#endif // !CAMERA_H
