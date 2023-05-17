#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline float degrees_to_radians(float degrees) 
{
    return degrees * pi / 180.0;
}

inline float random_float()
{
    return rand() / (RAND_MAX + 1.0f);
}
inline float random_float(float min, float max)
{
    return min + (max - min) * random_float();
}

inline float clamp(float x, float MIN, float MAX)
{
    if (x < MIN) return MIN;
    if (x > MAX) return MAX;
    return x;
}

#include "ray.h"
#include "vec3.h"