#include "ModuleEngineManager.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include "App.h"

ModuleEngineManager::ModuleEngineManager(bool startEnabled) : Module(startEnabled)
{
    name = "renderer";
}

ModuleEngineManager::~ModuleEngineManager() {}

void ModuleEngineManager::Awake() {
    engine.engineCamera.get()->AddComponent(Component::CAMERA);
    engine.engineCamera.get()->GetComponent<ComponentCamera>()->fov = 60;
    engine.engineCamera.get()->GetComponent<ComponentCamera>()->aspect = static_cast<double>(WIN_WIDTH) / WIN_HEIGHT;
    engine.engineCamera.get()->GetComponent<ComponentCamera>()->zNear = 0.1;
    engine.engineCamera.get()->GetComponent<ComponentCamera>()->zFar = 100;
    engine.engineCamera.get()->GetComponent<ComponentTransform>()->PositionSetter(vec3(5, 1.75, 5));
    engine.engineCamera.get()->GetComponent<ComponentCamera>()->lookAtPos = vec3(0, 1, 0);
    engine.engineCamera.get()->GetComponent<ComponentTransform>()->UpSetter(vec3(0, 1, 0));

    grid_xz = true;
    grid_xy = false;
    grid_zy = false;

    engine.CreateScene("Scene1");
    sel_Scene.index = 0;
    sel_Scene.scene = engine.GetSceneAtIndex(sel_Scene.index);
    sel_Scene.scene->loadFromFile("BakerHouse.fbx", sel_Scene.scene);
    //sel_GameObject.gameObject = sel_Scene.scene->gameObjects.front().get();
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
    
    MainCameraUpdate();
            
    return true;
}

bool ModuleEngineManager::PostUpdate() {
    
    if (app->gui->w_scene->GetWindowState() == States::ENABLED) {
        app->gui->w_scene->SceneFBO.Bind_FrameBuffer();

        engine.drawAxis();
        engine.drawGrid(100, 1, grid_xy, grid_xz, grid_zy);
        sel_Scene.scene->GameObjectsUpdate();

        app->gui->w_scene->SceneFBO.Unbind_FrameBuffer();
    }
    else {
        engine.drawAxis();
        engine.drawGrid(100, 1, grid_xy, grid_xz, grid_zy);
        sel_Scene.scene->GameObjectsUpdate();
    }    
        
    return true;
}

void ModuleEngineManager::CleanUp() {

}

void ModuleEngineManager::MainCameraUpdate() {
    auto cameraTransform = engine.engineCamera.get()->GetComponent<ComponentTransform>();

    if (app->events->GetMouseButton(SDL_BUTTON_RIGHT)) {
        

        //Rotate the camera based on mouse movement
        //RotateCameraYaw(engine.camera, -deltaX);
        //RotateCameraPitch(engine.camera, -deltaY); // Implement this function to rotate pitch



        if (app->events->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN) {
            camSpeed = 0.2;
        }
        if (app->events->GetKey(SDL_SCANCODE_LSHIFT) == KEY_UP) {
            camSpeed = 0.1;
        }

        if (app->events->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
        {
            cameraTransform->translate(vec3(0, 0, camSpeed));
        }
        if (app->events->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
        {
            cameraTransform->translate(vec3(0, 0, -camSpeed));
        }
        if (app->events->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
        {
            cameraTransform->translate(vec3(camSpeed, 0, 0));
        }
        if (app->events->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
        {
            cameraTransform->translate(vec3(-camSpeed, 0, 0));
        }
        if (app->events->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
        {
            cameraTransform->translate(vec3(0, camSpeed, 0));
        }
        if (app->events->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
        {
            cameraTransform->translate(vec3(0, -camSpeed, 0));
        }

        double sensitivity = 0.1; // Adjust sensitivity as needed
        double deltaX = app->events->GetMouseMotionX();
        double deltaY = app->events->GetMouseMotionY();
        
        cameraTransform->setRotation(vec3(0, deltaX * sensitivity, 0), ComponentTransform::Space::GLOBAL);
        cameraTransform->setRotation(vec3(deltaY * sensitivity, 0, 0), ComponentTransform::Space::LOCAL);
    }

    if (app->events->GetKey(SDL_SCANCODE_LALT)) {
        if (app->events->GetMouseButton(SDL_BUTTON_LEFT)) {

        }
        if (app->events->GetMouseButton(SDL_BUTTON_MIDDLE)) {

        }
    }


    }