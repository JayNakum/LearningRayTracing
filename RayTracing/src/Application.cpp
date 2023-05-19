#include "ray.h"
#include "vec3.h"

#include "Camera.h"
#include "Color.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"
#include "Utility.h"

#include <iostream>

color rayColor(const ray& r, const Hittable& world, int depth)
{
    HitRecord record;
 
    if (depth <= 0) return color(0, 0, 0);
    
    if (world.hit(r, 0.001f, infinity, record))
    {
        ray scattered;
        color attenuation;

        if (record.material->scatter(r, record, attenuation, scattered))
            return attenuation * rayColor(scattered, world, depth-1);
        return color(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

HittableList random_scene() {
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            point3 center(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main() 
{
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixels = 100;
    const int max_depth = 50;

    HittableList world = random_scene();

    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1f;

    Camera camera(lookfrom, lookat, vup, 20, aspectRatio, aperture, dist_to_focus);

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
