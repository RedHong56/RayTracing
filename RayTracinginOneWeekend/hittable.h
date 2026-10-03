#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"
#include "rtweekend.h"

class HitRecord
{
public:
	// sets the normal based on the ray direction and the outward normal
	void SetFaceNormal(const Ray& r, const Vec3& outwardNormal) //outNormal has to be normalized
    {
        bFrontFace = Dot(r.Direction(), outwardNormal) < 0;
        Normal = bFrontFace ? outwardNormal : -outwardNormal;
    }

    Point3 P;
    Vec3 Normal;
    double T;
    bool bFrontFace;
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool Hit(
        const Ray& ray, 
        const Interval& rayT,
        HitRecord& hitrecord
    ) const = 0;
};

#endif