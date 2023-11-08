#include "EngineGlobals.h"
#include "Camera.h"

Camera::Camera() : fov(60), aspect(4.0/3.0), clippingPlaneNear(0.1), clippingPlaneFar(100), position(10, 2, 10), orientation(0, 1, 0), up(0, 1, 0) {}

glm::dmat4 Camera::computeLookAt() const {
	return glm::lookAt(position, orientation, up);
}