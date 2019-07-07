#include "Ray.h"

Ray::Ray() : origin(Vector()), direction(Vector(1.0,0.0,0.0)) {} // a default ray starts at the origin and is moving in the x direction

Ray::Ray(Vector v, Vector u) : origin(v), direction(u) {}