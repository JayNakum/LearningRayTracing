#pragma once

#include "Core.h"

class Camera
{
public:
	Camera()
	{
		float aspectRatio = 16.0f / 9.0f;
		float viewportHeight = 2.0f;
		float viewportWidth = aspectRatio * viewportHeight;
		float focalLength = 1.0f;

		m_origin = point3(0, 0, 0);
		m_horizontal = vec3(viewportWidth, 0, 0);
		m_vertical = vec3(0, viewportHeight, 0);
		m_lowerLeftCorner = m_origin - m_horizontal/2 - m_vertical/2 - vec3(0, 0, focalLength);
	}

	ray getRay(float u, float v)
	{
		return ray(m_origin, m_lowerLeftCorner + u*m_horizontal + v*m_vertical - m_origin);
	}

private:
	point3 m_origin;
	point3 m_lowerLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
};