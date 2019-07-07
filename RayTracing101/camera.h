#pragma once
#include "VectorsCustom.h"

struct Camera
{
	Vector camPosition, camDirection, camRight, camDown;

	Camera();
	Camera(Vector position, Vector direction, Vector right, Vector down);
};

