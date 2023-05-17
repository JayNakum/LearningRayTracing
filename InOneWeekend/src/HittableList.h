#pragma once

#include "Hittable.h"

#include <vector>
#include <memory>

class HittableList : public Hittable
{
private:
	std::vector<std::shared_ptr<Hittable>> m_objects;

public:
	HittableList() = default;
	HittableList(std::shared_ptr<Hittable> object);

	void clear();
	void add(std::shared_ptr<Hittable> object);

	virtual bool hit(const ray& r, float t_min, float t_max, HitRecord& record) const override;
};
