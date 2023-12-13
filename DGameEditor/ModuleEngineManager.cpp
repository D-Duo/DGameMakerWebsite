#include "ModuleEngineManager.h"
#include "App.h"


#pragma region Camera functions

void MoveCameraForward(Camera& camera, double distance) {
    glm::dvec3 forward = glm::normalize(camera.center - camera.eye);
    camera.eye += forward * distance;
    camera.center += forward * distance;
}

void MoveCameraBackward(Camera& camera, double distance) {
    glm::dvec3 forward = glm::normalize(camera.center - camera.eye);
    camera.eye -= forward * distance;
    camera.center -= forward * distance;
}

void MoveCameraLeft(Camera& camera, double distance) {
    glm::dvec3 forward = glm::normalize(camera.center - camera.eye);
    glm::dvec3 right = glm::normalize(glm::cross(forward, camera.up));
    camera.eye -= right * distance;
    camera.center -= right * distance;
}

void MoveCameraRight(Camera& camera, double distance) {
    glm::dvec3 forward = glm::normalize(camera.center - camera.eye);
    glm::dvec3 right = glm::normalize(glm::cross(forward, camera.up));
    camera.eye += right * distance;
    camera.center += right * distance;
}

void MoveCameraUp(Camera& camera, double distance) {
    camera.eye += camera.up * distance;
    camera.center += camera.up * distance;
}

void MoveCameraDown(Camera& camera, double distance) {
    camera.eye -= camera.up * distance;
    camera.center -= camera.up * distance;
}

void RotateCameraAroundUpAxis(Camera& camera, double angle) {
    glm::dmat4 rotation = glm::rotate(glm::dmat4(1.0), angle, camera.up);
    glm::dvec3 new_eye = glm::vec3(rotation * glm::dvec4(camera.eye, 1.0));
    camera.center = camera.center - camera.eye + new_eye;
    camera.eye = new_eye;
}

void RotateCameraPitch(Camera& camera, double angle) {
    glm::dvec3 forward = glm::normalize(camera.center - camera.eye);
    glm::dvec3 right = glm::normalize(glm::cross(forward, camera.up));

    // Calculate the new forward vector after pitch rotation
    glm::dmat4 pitchRotation = glm::rotate(glm::dmat4(1.0), angle, right);
    glm::dvec3 newForward = glm::vec3(pitchRotation * glm::dvec4(forward, 0.0));

    // Calculate the new right vector after pitch rotation
    glm::dvec3 newRight = glm::normalize(glm::cross(newForward, camera.up));

    // Update the camera's center, up, and right vectors
    camera.center = camera.eye + newForward;
    camera.up = glm::cross(newRight, newForward);
}

void RotateCameraYaw(Camera& camera, double angle) {
    // Create a rotation matrix around the camera's up vector (yaw rotation)
    glm::dmat4 rotation = glm::rotate(glm::dmat4(1.0), angle, camera.up);

    // Calculate the new eye and center positions after rotation
    glm::dvec3 new_eye = glm::vec3(rotation * glm::dvec4(camera.eye - camera.center, 0.0));

    // Update the camera's eye and center vectors
    camera.eye = camera.center + new_eye;
}

#pragma endregion

ModuleEngineManager::ModuleEngineManager(bool startEnabled) : Module(startEnabled)
{
    name = "renderer";
}

ModuleEngineManager::~ModuleEngineManager() {}

void ModuleEngineManager::Awake() {
    engine.camera.fov = 60;
    engine.camera.aspect = static_cast<double>(WIN_WIDTH) / WIN_HEIGHT;
    engine.camera.zNear = 0.1;
    engine.camera.zFar = 100;
    engine.camera.eye = vec3(5, 1.75, 5);
    engine.camera.center = vec3(0, 1, 0);
    engine.camera.up = vec3(0, 1, 0);

    grid_xz = true;
    grid_xy = false;
    grid_zy = false;

    engine.CreateScene("Scene1");
    sel_Scene.index = 0;
    sel_Scene.scene = engine.GetSceneAtIndex(sel_Scene.index);
    sel_Scene.scene->loadFromFile("BakerHouse.fbx", sel_Scene.scene);
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

    if (app->events->GetMouseButton(SDL_BUTTON_RIGHT)) {
        double sensitivity = 0.01; // Adjust sensitivity as needed
        double deltaX = app->events->GetMouseMotionX() * sensitivity;
        double deltaY = app->events->GetMouseMotionY() * sensitivity;

        // Rotate the camera based on mouse movement
        RotateCameraYaw(engine.camera, -deltaX);
        RotateCameraPitch(engine.camera, -deltaY); // Implement this function to rotate pitch

        float camSpeed = 0.1;

        if (app->events->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN) { camSpeed = 0.2; }
        if (app->events->GetKey(SDL_SCANCODE_LSHIFT) == KEY_UP) { camSpeed = 0.1; }

        if (app->events->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
        {
            MoveCameraForward(engine.camera, camSpeed);
        }
        if (app->events->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
        {
            MoveCameraBackward(engine.camera, camSpeed);
        }
        if (app->events->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
        {
            MoveCameraLeft(engine.camera, camSpeed);
        }
        if (app->events->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
        {
            MoveCameraRight(engine.camera, camSpeed);
        }
        if (app->events->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
        {
            MoveCameraUp(engine.camera, camSpeed);
        }
        if (app->events->GetKey(SDL_SCANCODE_LCTRL) == KEY_REPEAT)
        {
            MoveCameraDown(engine.camera, camSpeed);
        }
    }

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