#pragma once
#include "EditorGlobals.h"

static bool PopupWindowsUpdate() {
    if (ImGui::BeginPopupModal("Settings Window", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("This is a modal window.");

        ImGui::EndPopup();
    }

    /*if (ImGui::BeginPopupModal("About this engine...", &App->editor->show_about_window, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("%s\nA simple engine for 3D game development.\nBy %s, %s", App->GetTitle(), App->GetAuthors(), App->GetOrganization());
        ImGui::Separator();

        ImGui::Text("3rd Party Libraries used:\n");
        ImGui::Bullet();
        if (ImGui::SmallButton("STL (C++11)")) {
            app->RequestBrowser("https://www.geeksforgeeks.org/the-c-standard-template-library-stl/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("SDL (v2.0.10)")) {
            app->RequestBrowser("https://www.libsdl.org/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("OpenGL (v3.1.0)")) {
            app->RequestBrowser("https://www.opengl.org/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("DevIL (v1.8.0)")) {
            app->RequestBrowser("http://openil.sourceforge.net/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("Assimp (v5.0.0)")) {
            app->RequestBrowser("http://assimp.org/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("Dear ImGui (v1.73, Base Code)")) {
            app->RequestBrowser("https://github.com/ocornut/imgui");
        }
        ImGui::Text("  "); ImGui::SameLine();
        if (ImGui::SmallButton("Docking Test Branch (Commit 18/10/19)")) {
            app->RequestBrowser("https://github.com/ocornut/imgui/tree/7feccf9ab2fad261aa873dfa067e64ad9fab8a03");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("glew (v2.0)")) {
            app->RequestBrowser("http://glew.sourceforge.net/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("MathGeoLib (v1.5)")) {
            app->RequestBrowser("https://github.com/juj/MathGeoLib");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("Par (vN/A)")) {
            app->RequestBrowser("https://github.com/prideout/par");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("JSON for Modern C++ (v3.7.0)")) {
            app->RequestBrowser("https://github.com/nlohmann/json");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("Brofiler (v1.1.2)")) {
            app->RequestBrowser("http://www.brofiler.com/");
        }
        ImGui::Bullet();
        if (ImGui::SmallButton("mmgr (vN/A)")) {
            app->RequestBrowser("http://www.flipcode.com/archives/Presenting_A_Memory_Manager.shtml");
        }

        ImGui::Separator();

        if (ImGui::CollapsingHeader("License")) {
            ImGui::PushTextWrapPos(App->editor->standard_text_width);
            ImGui::Text(App->GetLicense());
            ImGui::PopTextWrapPos();
        }

        ImGui::EndPopup();
    }*/

	return true;
}