#pragma once

#include "VectorsCustom.h"

struct Color
{
	float red, blue, green, special;

	Color(); // default color constructor
	Color(float red, float blue, float green, float special); //user specified color settings
	Color(const Color& color); // copy a color object

	float brightness();
	void clip(); // adjust the color values to keep them within the range of 0 - 1
	Color& operator *(float scalar);
	Color& operator +=(const Color& additive);
	Color& operator /(float divisor);
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

inline Color operator *(const Color& color1, const Color& color2)
{
	return Color(color1.red * color2.red, color1.blue * color2.blue, color1.green * color2.green, color1.special);
}

inline Color operator +(const Color& color1, const Color& color2)
{
	return Color(color1.red + color2.red, color1.blue + color2.blue, color1.green + color2.green, color1.special);
}