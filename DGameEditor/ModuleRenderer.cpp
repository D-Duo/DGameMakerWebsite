#include "ModuleRenderer.h"
#include "App.h"

ModuleRenderer::ModuleRenderer(bool startEnabled) : Module(startEnabled) {}

ModuleRenderer::~ModuleRenderer() {}

void ModuleRenderer::Awake() {

}

void ModuleRenderer::Start() {
    engine.camera.fov = 60;
    engine.camera.aspect = static_cast<double>(WIN_WIDTH) / WIN_HEIGHT;
    engine.camera.zNear = 0.1;
    engine.camera.zFar = 100;
    engine.camera.eye = vec3(5, 1.75, 5);
    engine.camera.center = vec3(0, 1, 0);
    engine.camera.up = vec3(0, 1, 0);
}

bool ModuleRenderer::PreUpdate() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    return true;
}

bool ModuleRenderer::Update(double dt) {
    engine.step(app->GetDeltaTime());    

    return true;
}

bool ModuleRenderer::PostUpdate() {
    ImGui::Render();

    engine.render(GameEngine::RenderModes::DEBUG); //engine render

    SDL_GL_SwapWindow(window);

    //render of modules

    return true;
}