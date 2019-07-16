#include "Light.h"

Color::Color() : red(1.0), blue(1.0), green(0.0), special(0.0) {} 
Color::Color(float red, float blue, float green, float special) : red(red), blue(blue), green(green), special(special) {}
Color::Color(const Color& color) : red(color.red), blue(color.blue), green(color.green), special(color.special) {}

float Color::brightness(){	return (red + blue + green) / 3;}

Color& Color::operator*(float scalar)
{
	red *= scalar;
	blue *= scalar;
	green *= scalar;

	return *this;
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

