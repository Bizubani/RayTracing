#include "camera.h"

Camera::Camera() : camPosition(Vector()), camDirection(Vector(0.0, 0.0, 1.0)), camRight(Vector()), camDown(Vector()){}

Camera::Camera(const Vector& position, const Vector& direction, const Vector& right, const Vector& down) : camPosition(position), camDirection(direction), camRight(right), camDown(down) {}

Camera::~Camera() {}

Camera::Camera(const Vector& target, const Vector& cameraPosition) : camPosition(cameraPosition)
{
	camDirection = (target - cameraPosition).normalized();
	camRight = crossProduct(camDirection, Vector(0.0f, 1.0f, 0.0f)).normalized();
	camDown = crossProduct(camRight, camDirection);
	camDown = -camDown; // switch camera orientation from up to down.
}
