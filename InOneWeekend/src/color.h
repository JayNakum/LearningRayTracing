#pragma once

#include "Core.h"
#include <iostream>

void write_color(std::ostream& out, const color& pixel, int samplesPerPixel)
{
    float r = pixel.r();
    float g = pixel.g();
    float b = pixel.b();

    float scale = 1.0f / samplesPerPixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0f, 0.999f)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0f, 0.999f)) << '\n';
}
