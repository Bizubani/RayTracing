#include "camera.h"

Camera::Camera() : camPosition(Vector()), camDirection(Vector(0.0, 0.0, 1.0)), camRight(Vector()), camDown(Vector()){}

Camera::Camera(Vector position, Vector direction, Vector right, Vector down) : camPosition(position), camDirection(direction), camRight(right), camDown(down) {}
