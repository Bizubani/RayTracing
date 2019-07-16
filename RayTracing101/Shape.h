#pragma once
#include <vector>

#include "Ray.h"
#include "VectorsCustom.h"
#include "Light.h"

class Shape // pure abstract shape class
{
public:
	virtual bool findIntersect(Intersection& intersection) = 0; // creates abstract member function that will be implemented to calculate the intersection of the shape and the ray
	virtual bool doesItIntersect(const Ray& ray) = 0; // creates abstract member function that will simply check whether a ray has intersected the shape
	virtual Color getColor() = 0;
	virtual void setColor(const Color& newColor) = 0;
	virtual ~Shape() {}
	virtual Vector getNormal(const Vector& intersect) = 0;
};

//composite class to hold the shapes in the scene
class ShapeSet
{
protected:
	std::vector<Shape*> shapes;

public:	
	ShapeSet();
	virtual ~ShapeSet();
	void addShape(Shape* shape);
	virtual bool findIntersect(Intersection& intersection);
	virtual bool doesItIntersect(const Ray& ray);
};

class Plane : public Shape
{
protected:
	Point position;// might be necessary to dot this with itself
	Vector normalToTheSurface;
	Color planeColor;

	//Todo: consider changing to distance
public:
	Plane(const Point& position, const Vector& normal, Color color);
	Plane();

	virtual ~Plane();
	virtual Color getColor();
	virtual void setColor(const Color& newColor);
	virtual bool findIntersect(Intersection& intersection);
	virtual bool doesItIntersect(const Ray& ray);
	virtual Vector getNormal(const Vector& intersect);
};

class Sphere : public Shape
{
protected:
	Point centerPoint;
	float radius;
	Color sphereColor;

public:
	Sphere(const Point& center, float radius, Color color);
	Sphere();
	//add getters for centerPoint and color
	virtual Color getColor();
	virtual void setColor(const Color& newColor);
	Point getCenter();
	
	virtual ~Sphere();
	virtual Vector getNormal(const Vector& intersect);
	virtual bool findIntersect(Intersection& intersection);
	virtual bool doesItIntersect(const Ray& ray);
};
