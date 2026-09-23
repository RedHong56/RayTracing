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

// Utility functions
inline std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
	return out << v.E[0] << ' ' << v.E[1] << ' ' << v.E[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v)
{
	return Vector3(u.E[0] + v.E[0], u.E[1] + v.E[1], u.E[2] + v.E[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v)
{
	return Vector3(u.E[0] - v.E[0], u.E[1] - v.E[1], u.E[2] - v.E[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v)
{
	return Vector3(u.E[0] * v.E[0], u.E[1] * v.E[1], u.E[2] * v.E[2]);
}

inline Vector3 operator*(double t, const Vector3& v)
{
	return Vector3(t * v.E[0], t * v.E[1], t * v.E[2]);
}

inline Vector3 operator*(const Vector3& v, double t)
{
	return t * v;
}

inline Vector3 operator/(Vector3 v, double t)
{
	return (1 / t) * v;
}

inline double Dot(const Vector3& u, const Vector3& v)
{
	return u.E[0] * v.E[0] 
		+ u.E[1] * v.E[1] 
		+ u.E[2] * v.E[2];
}

inline Vector3 Cross(const Vector3& u, const Vector3& v)
{
	return Vector3(u.E[1] * v.E[2] - u.E[2] * v.E[1],
		u.E[2] * v.E[0] - u.E[0] * v.E[2],
		u.E[0] * v.E[1] - u.E[1] * v.E[0]);
}

inline Vector3 UnitVector(Vector3 v)
{
	return v / v.Length();
}

#endif // VEC3_H