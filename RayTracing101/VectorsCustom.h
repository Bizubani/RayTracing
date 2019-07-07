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

