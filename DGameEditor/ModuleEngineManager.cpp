#include "ModuleEngineManager.h"
#include "App.h"

ModuleEngineManager::ModuleEngineManager(bool startEnabled) : Module(startEnabled)
{
    name = "renderer";
}

ModuleEngineManager::~ModuleEngineManager() {}

void ModuleEngineManager::Awake() {
    engine.mainCamera.fov = 60;
    engine.mainCamera.aspect = static_cast<double>(WIN_WIDTH) / WIN_HEIGHT;
    engine.mainCamera.clippingPlaneNear = 0.1;
    engine.mainCamera.clippingPlaneFar = 100;
    engine.mainCamera.position = vec3(5, 1.75, 5);
    engine.mainCamera.orientation = vec3(0, 1, 0);
    engine.mainCamera.up = vec3(0, 1, 0);

    grid_xz = true;
    grid_xy = false;
    grid_zy = false;

    engine.CreateScene("Scene1");
    sel_Scene.index = 0;
    sel_Scene.scene = engine.GetSceneAtIndex(sel_Scene.index);

    sel_Scene.scene.get()->loadFromFile("BakerHouse.fbx", sel_Scene.scene);
}

void ModuleEngineManager::Start() {

}

bool ModuleEngineManager::PreUpdate() {
    if (app->gui->w_scene->GetWindowState() == States::ENABLED) {
        app->gui->w_scene->SceneFBO.Bind_FrameBuffer();

        engine.render(); //engine render

        app->gui->w_scene->SceneFBO.Unbind_FrameBuffer();
    }
    else {
        engine.render(); //engine render
    }

    return true;
}

bool ModuleEngineManager::Update(duration<double> dt) {
    

    return true;
}

bool ModuleEngineManager::PostUpdate() {
    if (app->gui->w_scene->GetWindowState() == States::ENABLED) {
        app->gui->w_scene->SceneFBO.Bind_FrameBuffer();

        engine.drawAxis();
        engine.drawGrid(100, 1, grid_xy, grid_xz, grid_zy);
        sel_Scene.scene.get()->GameObjectsUpdate();

        app->gui->w_scene->SceneFBO.Unbind_FrameBuffer();
    }
    else {
        engine.drawAxis();
        engine.drawGrid(100, 1, grid_xy, grid_xz, grid_zy);
        sel_Scene.scene.get()->GameObjectsUpdate();
    }    

    return true;
}

void ModuleEngineManager::CleanUp() {

}