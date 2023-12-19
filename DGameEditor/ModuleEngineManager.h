#pragma once

#include "Module.h"

#include "..\DGameEngine\DGameEngine.h"

struct EngineScene
{
    shared_ptr<Scene> scene;
    int index;
};

struct SceneGO
{
    shared_ptr<GameObject> gameObject;
    int index;
};

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

    void MainCameraUpdate();

    GameEngine* GetEngine()  {
        return &engine;
    }

public:
    bool grid_xz, grid_xy, grid_zy;

    EngineScene sel_Scene;
    SceneGO sel_GameObject;

private:
    GameEngine engine;
    float camSpeed = 0.1;
};

