#pragma once

#include "EngineGlobals.h"
#include "Components.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera();

	void update() override;

	Type getType() const override {
		return Type::CAMERA;
	}

	double fov;
	double aspect;
	double zNear;
	double zFar;

	vec3 lookAtPos;
	double camOffset;

private:
	ComponentCamera(const ComponentCamera& cpy) = delete;
	ComponentCamera& operator=(const ComponentCamera&) = delete;
};