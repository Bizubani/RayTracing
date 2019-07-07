#include "VectorsCustom.h"

Vector::Vector() : x(0.0), y(0.0), z(0.0){}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

Vector::Vector(float f) : x(f), y(f), z(f) {}

Vector::~Vector() {}

inline float Vector::lengthSquared()
{
	return sqr(x) + sqr(y) + sqr(z); // return the sum of the squares of each axis
}

inline float Vector::length() 
{ 
	return sqrt(lengthSquared()); // return the square root of the sum of squares
}

float Vector::normalize()
{
	float vectorLength = length();
	
	*this /= vectorLength;

	return vectorLength;
} // normalize the current vector

Vector Vector::normalized()
{
	Vector v(*this);

	v.normalize();

	return v;
} // create a copy of the current vector, normalize it and return the value

Vector& Vector::operator =(const Vector& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}// assign one vector to another

Vector& Vector::operator+= (const Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
} // add a vector to this vector

Vector& Vector::operator-= (const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
} // subtract a vector form this vector

Vector& Vector::operator*= (float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
} // scalar multiplication

Vector& Vector::operator/= (float f)
{
	x /= f;
	y /= f;
	z /= f;

	return *this;
} // used in normalization of vectors

Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
} // reverse the vector by multipling all axises by -1

float Vector::dotProduct(Vector v)
{
	return v.x * x + v.y * y + v.z * z;
}

Vector Vector::crossProduct(Vector v)
{
	return Vector(
		v.y * z - v.z * y, // calculate value of x
		v.z * x - v.x * z, // calculate value of y
		v.x * y - v.y * x); // calculate value of z
}

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
	return Vector(f / v.x, f /v.y, f / v.z);
} 
