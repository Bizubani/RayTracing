#pragma once
#include <math.h>

inline float sqr (float n) { return n * n; }

struct Vector
{
	float x, y, z;

	Vector(); //default constructor
	Vector(float x, float y, float z); // user defined constructor
	Vector(const Vector & v); // copy constructor
	Vector(float f); // singled variable constructor

	inline float lengthSquared();
	inline float length();

	float normalize(); // normalize the current vector. Works in place.
	Vector normalized(); // return a copy of the current vector that has been normalized

	float dotProduct(Vector v); // calculate the dot product of the current vector dot v
	Vector crossProduct(Vector v); // calculate the cross product of the current vector cross v

	virtual ~Vector(); // deconstructor

	Vector& operator = (const Vector& v);
	Vector& operator +=(const Vector& v);
	Vector& operator -=(const Vector& v);
	Vector& operator /=(float f);
	Vector& operator *=(float f);
	Vector operator -() const;

};

typedef Vector Point;

inline Vector operator +(const Vector& v, const Vector& u)
{
	return Vector(v.x + u.x, v.y + u.y, v.z + u.z);
} // sum two vectors and return a new vector

inline Vector operator - (const Vector& v, const Vector& u)
{
	return Vector(v.x - u.x, v.y - u.y, v.z - u.z);
} //take the difference of two vectors and return a new vector

inline Vector operator *(const Vector& v, const float f)
{
	return Vector(v.x * f, v.y * f, v.z * f);
} //scale a vector v by f

inline Vector operator *(const float f, const Vector& v)
{
	return Vector(v.x * f, v.y * f, v.z * f);
} // scale a vector v by f

inline Vector operator /(const Vector& v, const float f)
{
	return Vector(v.x / f, v.y / f, v.z / f);
} //shrink a vector by f

inline Vector operator /(const float f, const Vector& v)
{
	return Vector(f / v.x, f / v.y, f / v.z);
}

inline float dotProduct(const Vector& v, const Vector& u)

{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

inline Vector crossProduct(const Vector& v, const Vector& u)
{
	return Vector(
		v.y * u.z - v.z * u.y, // calculate value of x
		v.z * u.x - v.x * u.z, // calculate value of y
		v.x * u.y - v.y * u.x); // calculate value of z
}