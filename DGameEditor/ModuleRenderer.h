#pragma once

#include "Module.h"

#include "..\DGameEngine\DGameEngine.h"

class ModuleRenderer : public Module
{
public:
	ModuleRenderer(bool startEnabled);
	~ModuleRenderer();

    void Awake();
    void Start();

    bool PreUpdate();
    bool Update(std::chrono::duration<double> dt);
    bool PostUpdate();

    void CleanUp();

private:
    GameEngine engine;
};

