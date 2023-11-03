#pragma once

#include "EngineGlobals.h"
#include "Camera.h"

class GameEngine
{
public:

	enum class RenderModes {RELEASE, DEBUG};

	Camera camera;

	void step(std::chrono::duration<double> dt);
	void render(RenderModes renderMode);

	bool grid_xy;
	bool grid_xz;
};

