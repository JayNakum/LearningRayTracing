#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "Hittable.h"

#include <vector>
#include <memory>

class HittableList : public Hittable
{
private:
	std::vector<std::shared_ptr<Hittable>> m_objects;

public:
	HittableList() {}
	HittableList(std::shared_ptr<Hittable> object)
	{
		add(object);
	}

	void clear()
	{
		m_objects.clear();
	}

	void add(std::shared_ptr<Hittable> object)
	{
		m_objects.push_back(object);
	}

	virtual bool hit(const ray& r, float t_min, float t_max, HitRecord& record) const override
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
};

#endif // !HITTABLELIST_H
