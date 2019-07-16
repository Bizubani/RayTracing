#pragma once 
#include "VectorsCustom.h"


//used to prevent bouncing rays self intersecting
#define RAY_T_MIN 0.0001f
// Maximum distance which is technically infinite
#define RAY_T_MAX 1.0e30f

struct Ray
{
	Point origin;
	Vector direction;
	float rayMax;

	Ray();
	Ray(const Vector& origin, const Vector& direction);
	Ray(const Vector& origin, const Vector& direction, const float maxRaySize);
	virtual ~Ray();

	Point calculateMove(float t) const;
};

class Shape;

struct Intersection
{
	Ray ray;
	float t;
	Shape* object;

	Intersection();
	Intersection(const Intersection& intersection);
	Intersection(const Ray& ray);
	~Intersection();

	bool intersected()const;
	Point positionOfIntersect()const;
};

