#include "Core.h"

#include "Color.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

#include <iostream>

color rayColor(const ray& r, const Hittable& world, int depth)
{
    HitRecord record;
 
    if (depth <= 0) return color(0, 0, 0);
    
    if (world.hit(r, 0.001f, infinity, record))
    {
        point3 target = record.p + random_in_hemisphere(record.normal);
        return 0.5f * rayColor(ray(record.p, target - record.p), world, depth-1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixels = 100;
    const int max_depth = 50;

    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5f));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera camera;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i) {
            color pixel(0, 0, 0);
            for (int s = 0; s < samplesPerPixels; ++s)
            {
                float u = (i + random_float()) / (imageWidth - 1);
                float v = (j + random_float()) / (imageHeight - 1);
                ray r = camera.getRay(u, v);
                pixel += rayColor(r, world, max_depth);
            }
            write_color(std::cout, pixel, samplesPerPixels);
        }
    }
    std::cerr << "\nDone.\n";
}
