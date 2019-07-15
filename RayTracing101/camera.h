#pragma once
#include "VectorsCustom.h"

struct Camera
{
	Vector camPosition, camDirection, camRight, camDown;

	Camera();
	Camera(const Vector& target, const Vector& cameraPositon);
	Camera(const Vector& position, const Vector& direction, const Vector& right, const Vector& down);
	virtual ~Camera();
};

