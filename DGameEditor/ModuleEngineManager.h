#pragma once

#include "Module.h"

#include "..\DGameEngine\DGameEngine.h"

class ModuleEngineManager : public Module
{
public:
    ModuleEngineManager(bool startEnabled);
    ~ModuleEngineManager();

    void Awake();
    void Start();

    bool PreUpdate();
    bool Update(std::chrono::duration<double> dt);
    bool PostUpdate();

    void CleanUp();

    GameEngine* GetEngine()  {
        return &engine;
    }

private:
    GameEngine engine;
};

