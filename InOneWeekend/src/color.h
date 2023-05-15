#pragma once

#include "vec3.h"
#include <iostream>

void write_color(std::ostream& out, const color& pixel)
{
    out << static_cast<int>(255.999 * pixel.r()) << ' '
        << static_cast<int>(255.999 * pixel.g()) << ' '
        << static_cast<int>(255.999 * pixel.b()) << '\n';
}
