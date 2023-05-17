#include "HittableList.h"

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
	add(object);
}

void HittableList::clear()
{
	m_objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
	m_objects.push_back(object);
}

bool HittableList::hit(const ray& r, float t_min, float t_max, HitRecord& record) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (const auto& object : m_objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            record = temp_rec;
        }
    }

    return hit_anything;
}
