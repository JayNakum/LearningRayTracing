#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
public:
	vec3()
		: m_e{0.0f, 0.0f, 0.0f} {}
	
	vec3(float e0, float e1, float e2)
		: m_e{e0, e1, e2} {}

	inline float x() const { return m_e[0]; }
	inline float y() const { return m_e[1]; }
	inline float z() const { return m_e[2]; }

	inline float r() const { return m_e[0]; }
	inline float g() const { return m_e[1]; }
	inline float b() const { return m_e[2]; }



private:
	float m_e[3];
};