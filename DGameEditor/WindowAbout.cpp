#include "WindowAbout.h"
#include "App.h"

WindowAbout::WindowAbout(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowAbout::PreUpdate() {
    int winw = 400;
    int winh = 300;
    ImGui::SetNextWindowSize(ImVec2(winw, winh));

    int winx, winy;
    SDL_Window* mainWin = app->window->GetWindow();
    SDL_GetWindowPosition(mainWin, &winx, &winy);

    winx += (app->window->GetWindowSize().x / 2) - (winw / 2);
    winy += (app->window->GetWindowSize().y / 2) - (winh / 2);
    ImGui::SetNextWindowPos(ImVec2(winx, winy));
}

void WindowAbout::Update() {    

    ImGui::TextWrapped("Name: %s\n\nCustom Game engine for 3D games, currently in development, created by students for the sillabus Game Engines of the degree Game Design & Development of the UPC in Barcelona.\n\nCreated by: %s\n\nMembers:\n", app->GetAppDetails().name.c_str(), app->GetAppDetails().org.name.c_str());

    for (const std::string& member : app->GetAppDetails().org.members) {
        ImGui::Text("%s\n", member.c_str());
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Resources")) {
        ImGui::Text("Package Manager:\n");
        ImGui::Bullet();
        if (ImGui::SmallButton("VCPKG")) {
            app->RequestBrowser("https://vcpkg.io/en/");
        }
        ImGui::Separator();
        ImGui::Text("3rd Party Libraries used:\n");
        ImGui::Bullet();
        if (ImGui::SmallButton("STL C++ Libraries")) {
            app->RequestBrowser("https://www.geeksforgeeks.org/the-c-standard-template-library-stl/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("SDL2 (v2.28.3)")) {
            app->RequestBrowser("https://www.libsdl.org");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("OpenGL")) {
            app->RequestBrowser("https://www.opengl.org");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("glew (v2.2)")) {
            app->RequestBrowser("https://glew.sourceforge.net");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("ImGui (v1.89.9)")) {
            app->RequestBrowser("https://github.com/ocornut/imgui");
        }
        ImGui::Text("  "); ImGui::SameLine();
        if (ImGui::SmallButton("ImGui Docking Test Branch")) {
            app->RequestBrowser("https://github.com/ocornut/imgui/tree/docking");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("GLM - Opengl Mathematics")) {
            app->RequestBrowser("https://www.opengl.org/sdk/libs/GLM/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("Assimp (v5.3.1)")) {
            app->RequestBrowser("https://assimp.org");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("DevIL (v1.8.0)")) {
            app->RequestBrowser("http://openil.sourceforge.net/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("JSON for Modern C++ (v3.7.0)")) {
            app->RequestBrowser("https://github.com/nlohmann/json");
        }       
    }
    ImGui::Separator();

    if (ImGui::CollapsingHeader("License")) {
        ImGui::TextWrapped("MIT License\n\n"
            "Copyright(c) 2023 D.Duo\n\n"
            "Permission is hereby granted, free of charge, to any person obtaining a copy"
            "of this software and associated documentation files (the \"Software\"), to deal"
            "in the Software without restriction, including without limitation the rights"
            "to use, copy, modify, merge, publish, distribute, sublicense, and /or sell"
            "copies of the Software, and to permit persons to whom the Software is"
            "furnished to do so, subject to the following conditions:\n\n"
            "The above copyright notice and this permission notice shall be included in all"
            "copies or substantial portions of the Software.\n\n"
            "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR"
            "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,"
            "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE"
            "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER"
            "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,"
            "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE"
            "SOFTWARE.");
    }
}