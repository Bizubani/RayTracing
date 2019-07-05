#pragma once
#include <math.h>

inline float sqr (float n) { return n * n; }

struct Vectors
{
	float x, y, z;

	Vectors(); //default constructor
	Vectors(float x, float y, float z); // user defined constructor
	Vectors(const Vectors & v); // copy constructor
	Vectors(float f); // singled variable constructor

	inline float lengthSquared();
	inline float length();

	float normalize();
	Vectors normalized();

	float dotProduct(Vectors v, Vectors u);
	Vectors crossProduct(Vectors v, Vectors u);

	virtual ~Vectors(); // deconstructor

	Vectors& operator = (const Vectors& v);
	Vectors& operator +=(const Vectors& v);
	Vectors& operator -=(const Vectors& v);
	Vectors& operator /=(float f);
	Vectors& operator *=(float f);
	Vectors operator -() const;

};

typedef Vectors Point;

