#include "Light.h"

Color::Color() : red(1.0), blue(1.0), green(0.0), special(0.0) {} 
Color::Color(float red, float blue, float green, float special) : red(red), blue(blue), green(green), special(special) {}
Color::Color(const Color& color) : red(color.red), blue(color.blue), green(color.green), special(color.special) {}

Light::Light() : position(Vector(0.0, 0.0, 0.0)), lightColor(Color()) {}
Light::Light(Vector position, Color lightColor) : position(position), lightColor(lightColor) {}
Light::Light(const Light& lightSource) : position(lightSource.position), lightColor(lightSource.lightColor) {}
