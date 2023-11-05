#pragma once

#include "EngineGlobals.h"
#include "Camera.h"
#include "CubeImmediateMode.h"

class GameEngine
{
public:

	enum class RenderModes {RELEASE, DEBUG};

	Camera camera;

	GameEngine();
	CubeImmediateMode* myCube;

	void step(std::chrono::duration<double> dt);
	void render(RenderModes renderMode);
};

