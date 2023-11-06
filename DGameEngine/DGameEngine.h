#pragma once

#include "EngineGlobals.h"
#include "Camera.h"
#include "CubeImmediateMode.h"
#include "Scene.h"

class GameEngine
{
public:

	enum class RenderModes {RELEASE, DEBUG};

	Camera camera;

	GameEngine();

	bool initB = true;

	Scene myScene;
	CubeImmediateMode* myCube;
	GameObject gameObj;

	void step(std::chrono::duration<double> dt);
	void render(RenderModes renderMode);

	bool grid_xy;
	bool grid_xz;
};

