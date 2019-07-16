#include "Shape.h"

ShapeSet::ShapeSet() {}
ShapeSet::~ShapeSet() {}

void ShapeSet::addShape(Shape* shape)
{
	shapes.push_back(shape);
}

bool ShapeSet::findIntersect(Intersection& intersection)
{
	bool doesItIntersect = false; // value that will be returned is initialized to false.
	for (std::vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); iter++)
	{
		Shape* currentShape = *iter;
		if (currentShape->findIntersect(intersection) == true)
		{
			doesItIntersect = true;
		}
	}
	return doesItIntersect;
}

bool ShapeSet::doesItIntersect(const Ray& ray)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin(); iter != shapes.end(); iter++)
	{
		Shape* currentShape = *iter;
		if (currentShape->doesItIntersect(ray) == true)
		{
			return true;
		}
	}
	return false;
}


Plane::Plane(const Point& point, const Vector& normal, Color color): position(point), normalToTheSurface(normal), planeColor(color) {}

Plane::Plane():position(1.0f, 0.0f, 0.0f), normalToTheSurface(0.0f, 0.0f, 10.0f), planeColor(Color(0.5f, 0.5f, 0.5f, 0.0f)) {}// Todo: Test before using default constructor

Plane::~Plane(){}

Color Plane::getColor() { return planeColor; }

void Plane::setColor(const Color& newColor) 
{
	planeColor.red = newColor.red; 
	planeColor.blue = newColor.blue;
	planeColor.green = newColor.green;
}

Vector Plane::getNormal(const Vector& intersect)
{
	return normalToTheSurface;
}

bool Plane::findIntersect(Intersection& intersection)
{
	float rayDotNormal = dotProduct(intersection.ray.direction, normalToTheSurface);

	if (rayDotNormal == 0.0f)
	{
		return false; //  if the ray is parallel to the surface, there will be no intersection. If the ray is in the surface we ignore it.
	}
	else
	{	// if there will be an intersection, calculate how far along the ray's path it occurs
		float t = dotProduct(position - intersection.ray.origin, normalToTheSurface) / rayDotNormal; //Todo: review this after to see if there are other

		// if the distance to intersection is too small or there is already an object in the way
		if (t <= RAY_T_MIN || t >= intersection.t)
		{
			return false; // discard this intersection
		}
		intersection.t = t; // this is the distance to the closest intersecting object found so far
		intersection.object = this; // and we store the object that we intersected with.

		return true;
	}
	
}

bool Plane::doesItIntersect(const Ray& ray)
{
	float rayDotNormal = dotProduct(ray.direction, normalToTheSurface);

	if (rayDotNormal == 0)
	{
		return false; // if the ray is parallel to the surface, there will be no intersection. If the ray is in the surface we ignore it.
	}
	else
	{
		float t = dotProduct(position - ray.origin, normalToTheSurface) / rayDotNormal;
		// if the distance to intersection is too small, or, it's too large
		if (t <= RAY_T_MIN || t >= ray.rayMax)
		{			
			return false;  // there is no intersection
		}
		return true; // tell the caller that the ray intersects with this object
	}
}

Sphere::Sphere(const Point& center, float radius, Color color) : centerPoint(center), radius(radius), sphereColor(color) {}
Sphere::Sphere() : centerPoint(Vector(0,0,0)), radius(1.0), sphereColor(Color(0.0f, 1.0f, 0.2f, 0.0f)){}
Sphere::~Sphere(){}

Point Sphere::getCenter() { return centerPoint; }
Color Sphere::getColor() { return sphereColor; }
void Sphere::setColor(const Color& newColor)
{
	sphereColor.red = newColor.red;
	sphereColor.blue = newColor.blue;
	sphereColor.green = newColor.green;
}

Vector Sphere::getNormal(const Vector& intersect) 
{
	return intersect - centerPoint;
}

bool Sphere::findIntersect(Intersection& intersection)
{
	Ray localRay = intersection.ray;
	localRay.origin -= centerPoint; // adjust the light ray to make it relative to the center point???? // Todo: Revise the mathematical theory

	///find the coefficients of the quadratic
	float a = localRay.direction.lengthSquared();
	float b = 2 * dotProduct(localRay.direction, localRay.origin);
	float c = localRay.origin.lengthSquared() - sqr(radius);

	//determine the discriminant of the quadratic and determine if there are intersections
	float discriminant = sqr(b) - 4 * a * c;

	// if the discriminant is negative, then there are no real roots and no intersection
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		///calculate the roots of the quadratic, if the discriminant is zero, t1 = t2
		float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
		float t2 = (-b + sqrt(discriminant)) / (2.0f * a);
		//if the first point of intersection is bigger than the min value and no object is closer
		if (t1 > RAY_T_MIN && t1 < intersection.t)
		{
			intersection.t = t1;
		}
		else if (t2 > RAY_T_MIN && t2 < intersection.t) 
		{
			intersection.t = t2;
		}
		else
		{
			return false; // another object is already in the way
		}

		intersection.object = this;  // this is now the closest shape intersecting this ray
		return true;
	}

}

bool Sphere::doesItIntersect(const Ray& ray)
{
	Ray localRay = ray;
	localRay.origin -= centerPoint; // adjust the light ray to make it relative to the center point????

	///find the coefficients of the quadratic
	float a = localRay.direction.lengthSquared();
	float b = 2 * dotProduct(localRay.direction, localRay.origin);
	float c = localRay.origin.lengthSquared() - sqr(radius);

	//determine the discriminant of the quadratic and determine if there are intersections
	float discriminant = sqr(b) - 4 * a * c;

	// if the discriminant is negative, then there are no real roots and no intersection
	if (discriminant < 0.0f)
	{
		return false;
	}
	else
	{
		///calculate the roots of the quadratic, if the discriminant is zero, t1 = t2
		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);
		//if the first point of intersection is bigger than the min value and no object is closer
		if (t1 > RAY_T_MIN && t1 < ray.rayMax)
		{
			return true;
		}
		if (t2 > RAY_T_MIN && t2 < ray.rayMax)
		{
			return true;
		}

		return false;
	}

}
