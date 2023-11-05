#include "WindowSettings.h"
#include "App.h"

WindowSettings::WindowSettings(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowSettings::PreUpdate() {
    int winw = 600;
    int winh = 450;
    ImGui::SetNextWindowSize(ImVec2(winw, winh));

    int winx, winy;
    SDL_Window* mainWin = app->window->GetWindow();
    SDL_GetWindowPosition(mainWin, &winx, &winy);

    winx += (app->window->GetWindowSize().x / 2) - (winw / 2);
    winy += (app->window->GetWindowSize().y / 2) - (winh / 2);
    ImGui::SetNextWindowPos(ImVec2(winx, winy));
}

void WindowSettings::Update() {

}