#pragma once

#include "VectorsCustom.h"

struct Color
{
	float red, blue, green, special;

	Color(); // default color constructor
	Color(float red, float blue, float green, float special); //user specified color settings
	Color(const Color& color); // copy a color object
};


struct Light
{
	Vector position;
	Color lightColor;

	Light();
	Light(const Vector& position, const Color& lightColor);
	Light(const Light& light);
	virtual ~Light();
};

