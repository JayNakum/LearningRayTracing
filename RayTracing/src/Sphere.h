#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable
{
public:
    Sphere() : m_center{ 0.0f, 0.0f, 0.0f }, m_radius(0.0f) {}
    Sphere(point3 center, float radius, std::shared_ptr<Material> material)
        : m_center(center), m_radius(radius), m_material(material) {}

    virtual bool hit(const ray& r, float t_min, float t_max, HitRecord& record) const override
    {
        vec3 oc = r.origin() - m_center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - m_radius * m_radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        record.t = root;
        record.p = r.at(record.t);
        vec3 outwardNormal = (record.p - m_center) / m_radius;
        record.setFaceNormal(r, outwardNormal);
        record.material = m_material;

        return true;
    }

private:
    point3 m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};

#endif // !SPHERE_H
