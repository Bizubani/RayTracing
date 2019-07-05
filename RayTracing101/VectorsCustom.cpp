#include "VectorsCustom.h"

Vectors::Vectors() : x(0.0), y(1.0), z(0.0){}

Vectors::Vectors(float x, float y, float z) : x(x), y(y), z(z) {}

Vectors::Vectors(const Vectors& v) : x(v.x), y(v.y), z(v.z) {}

Vectors::Vectors(float f) : x(f), y(f), z(f) {}

Vectors::~Vectors() {}

inline float Vectors::lengthSquared()
{
	return sqr(x) + sqr(y) + sqr(z); // return the sum of the squares of each axis
}

inline float Vectors::length() 
{ 
	return sqrt(lengthSquared()); // return the square root of the sum of squares
}

float Vectors::normalize()
{
	float vectorLength = length();
	
	*this /= vectorLength;

	return vectorLength;
} // normalize the current vector

Vectors Vectors::normalized()
{
	Vectors v(*this);

	v.normalize();

	return v;
} // create a copy of the current vector, normalize it and return the value

Vectors& Vectors::operator =(const Vectors& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}// assign one vector to another

Vectors& Vectors::operator+= (const Vectors& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
} // add a vector to this vector

Vectors& Vectors::operator-= (const Vectors& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
} // subtract a vector form this vector

Vectors& Vectors::operator*= (float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
} // scalar multiplication

Vectors& Vectors::operator/= (float f)
{
	x /= f;
	y /= f;
	z /= f;

	return *this;
} // used in normalization of vectors

Vectors Vectors::operator-() const
{
	return Vectors(-x, -y, -z);
} // reverse the vector by multipling all axises by -1

float Vectors::dotProduct(Vectors v, Vectors u)
{
	return v.x * u.x + v.y * u.y + v.z * u.z;
}

Vectors Vectors::crossProduct(Vectors v, Vectors u)
{
	return Vectors(
		v.y * u.z - v.z * u.y, // calculate value of x
		v.z * u.x - v.x * u.z, // calculate value of y
		v.x * u.y - v.y * u.x); // calculate value of z
}

inline Vectors operator +(const Vectors& v, const Vectors& u)
{
	return Vectors(v.x + u.x, v.y + u.y, v.z + u.z);
} // sum two vectors and return a new vector

inline Vectors operator - (const Vectors& v, const Vectors& u)
{
	return Vectors(v.x - u.x, v.y - u.y, v.z - u.z);
} //take the difference of two vectors and return a new vector

inline Vectors operator *(const Vectors& v, const float f)
{
	return Vectors(v.x * f, v.y * f, v.z * f);
}

inline Vectors operator *(const float f, const Vectors& v)
{
	return Vectors(v.x * f, v.y * f, v.z * f);
}

inline Vectors operator /(const Vectors& v, const float f)
{
	return Vectors(v.x / f, v.y / f, v.z / f);
}

inline Vectors operator /(const float f, const Vectors& v)
{
	return Vectors(v.x / f, v.y / f, v.z / f);
}
