#pragma once

#include "EngineGlobals.h"

struct Camera
{
	double fov;
	double aspect;
	double clippingPlaneNear;
	double clippingPlaneFar;

	vec3 position;
	vec3 orientation;
	vec3 up;

	mat4 computeLookAt() const;

	Camera();
};

