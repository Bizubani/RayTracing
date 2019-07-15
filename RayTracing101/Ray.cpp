#include "Ray.h"

Ray::Ray() : origin(Vector()), direction(Vector(1.0,0.0,0.0)), rayMax(RAY_T_MAX) {} // a default ray starts at the origin and is moving in the x direction

Ray::Ray(const Vector& v, const Vector& u) : origin(v), direction(u), rayMax(RAY_T_MAX) {}

Ray::~Ray() {}

Point Ray::calculateMove(float t) const
{
	return origin + direction * t; //calculate the distance moved using the formula p + d(t) where p is the origin of the ray, d is the direction of the ray and t is the scalar of d
}

Intersection::Intersection(): ray(), t(RAY_T_MAX), object(NULL){}

Intersection::Intersection(const Intersection& intersection): ray(intersection.ray), t(intersection.t), object(intersection.object) {}

Intersection::Intersection(const Ray& ray) :ray(ray), t(ray.rayMax), object(NULL) {}

Intersection::~Intersection() {};

bool Intersection::intersected() const
{
	return (object != NULL); // checks if the ray has intersected with an object.
}

Point Intersection::positionOfIntersect()const
{
	return ray.calculateMove(t); // calculates how far along the ray line the light hits an object.
}