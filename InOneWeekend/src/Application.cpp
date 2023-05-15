#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

float hitSphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0)
        return -1.0f;
    else
        return (-b - std::sqrt(discriminant)) / (2.0f * a);
}

color rayColor(const ray& r)
{
    float t = hitSphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0f)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5f * color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    float viewportHeight = 2.0f;
    float viewportWidth = aspectRatio * viewportHeight;
    float focalLength = 1.0f;

    point3 origin = point3(0.0f, 0.0f, 0.0f);
    vec3 horizontal = vec3(viewportWidth, 0, 0);
    vec3 vertical = vec3(0, viewportHeight, 0);
    vec3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLength);


    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            float u = (float)i / (imageWidth - 1);
            float v = (float)j / (imageHeight - 1);

            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            
            color pixel = rayColor(r);
            write_color(std::cout, pixel);
        }
    }
    std::cerr << "\nDone.\n";
}