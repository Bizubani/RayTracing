#include "Light.h"

Color::Color() : red(1.0), blue(1.0), green(0.0), special(0.0) {} 
Color::Color(float red, float blue, float green, float special) : red(red), blue(blue), green(green), special(special) {}
Color::Color(const Color& color) : red(color.red), blue(color.blue), green(color.green), special(color.special) {}

float Color::brightness(){	return (red + blue + green) / 3;}


void Color::clip()
{
	float totalRGB = red + blue + green;
	float excessLight = totalRGB - 3.0f;

	if (excessLight > 0)
	{	
		red = red + excessLight * (red / totalRGB);
		blue = blue + excessLight * (blue / totalRGB);
		green = green + excessLight * (green / totalRGB);
	}
	///after shifting the color values, if they are still outside the valid ranges, shift them to their maximun
	if (red > 1)
	{
		red = 1;
	}		
	if (green > 1)
	{
		green = 1;
	}
	if (blue > 1)
	{
		blue = 1;
	}

	///or their minimum as appropriate
	if (red < 0)
	{
		red = 0;
	}
	if (green < 0)
	{
		green = 0;
	}
	if (blue < 0)
	{
		blue = 0;
	}
}




Color& Color::operator +=(const Color& additive)
{
	red += additive.red;
	blue += additive.blue;
	green += additive.green;

	return *this;
}

Color& Color::operator/(float divisor)
{
	red /= divisor;
	blue /= divisor;
	green /= divisor;

	return *this;
}

Light::Light() : position(Vector(0.0, 0.0, 0.0)), lightColor(Color()) {}
Light::Light(const Vector& position, const Color& lightColor) : position(position), lightColor(lightColor) {}
Light::Light(const Light& lightSource) : position(lightSource.position), lightColor(lightSource.lightColor) {}

Light::~Light(){}

