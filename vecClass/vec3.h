#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

struct Vector3
{
	Vector3() : E{ 0, 0, 0 } {}
	Vector3(double e0, double e1, double e2) : E{ e0, e1, e2 } {}

	double x() const { return E[0]; }
	double y() const { return E[1]; }
	double z() const { return E[2]; }

	Vector3 operator-() const { return Vector3(-E[0], -E[1], -E[2]); }
	double operator[](int i) const { return E[i]; }
	double& operator[](int i) { return E[i]; }

	Vector3& operator+=(const Vector3& v)
	{
		E[0] += v.E[0];
		E[1] += v.E[1];
		E[2] += v.E[2];
		return *this;
	}

	Vector3& operator*=(const double t)
	{
		E[0] *= t;
		E[1] *= t;
		E[2] *= t;
		return *this;
	}

	Vector3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double Length() const
	{
		return std::sqrt(LengthSquared());
	}

	double LengthSquared() const
	{
		return E[0] * E[0] + E[1] * E[1] + E[2] * E[2];
	}

	// member variables
	double E[3]; // x, y, z
};
typedef Vector3 Vec3;
using Point3 = Vector3; // alias for 3D point

#endif // VEC3_H