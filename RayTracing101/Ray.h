#pragma once 
#include "VectorsCustom.h"

struct Ray
{
	Vector origin, direction;
	Ray();
	Ray(Vector v, Vector u);
};

