#include "EngineGlobals.h"
#include "ComponentCamera.h"
#include "GameObject.h"
#include "ComponentTransform.h"

ComponentCamera::ComponentCamera() : fov(60), aspect(4.0 / 3.0), zNear(0.1), zFar(100), camOffset(10) {}

void ComponentCamera::update() {}