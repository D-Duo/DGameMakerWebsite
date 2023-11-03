#pragma once

#include "EditorGlobals.h"

static bool MenuBarUpdate() {
    if (ImGui::BeginMenuBar()) {
        GameEngine* engine_p = app->engineManager->GetEngine();
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Scene", "Ctrl+N", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "New Scene" is selected
            }
            if (ImGui::MenuItem("Open Scene", "Ctrl+O", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Open Scene" is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Save", "Ctrl+S", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Save" is selected
            }
            if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Save As..." is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("New Project...", NULL, false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "New Project..." is selected
            }
            if (ImGui::MenuItem("Open Project...", NULL, false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Open Project..." is selected
            }
            if (ImGui::MenuItem("Save Project", NULL, false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Save Project" is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit", NULL, false)) {
                return false;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Undo" is selected
            }
            if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Redo" is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Select All", "Ctrl+A", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Select All" is selected
            }
            if (ImGui::MenuItem("Deselect All", "Shift+D", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Deselect All" is selected
            }
            if (ImGui::MenuItem("Select Children", "Shift+C", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Select Children" is selected
            }
            if (ImGui::MenuItem("Invert Selection", "Ctrl+I", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Invert Selection" is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Duplicate", "Ctrl+D", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Duplicate" is selected
            }
            if (ImGui::MenuItem("Rename", NULL, false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Rename" is selected
            }
            if (ImGui::MenuItem("Delete", NULL, false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Delete" is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Play", "Ctrl+P", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Play" is selected
            }
            if (ImGui::MenuItem("Pause", "Ctrl+Shift+P", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Pause" is selected
            }
            if (ImGui::MenuItem("Step", "Ctrl+Alt+P", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Step" is selected
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Settings...")) {
                ImGui::OpenPopup("MyPopup"); // Open the modal popup when the button is clicked.
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            if (ImGui::Checkbox("Grid XY", &engine_p->grid_xy));

            if (ImGui::Checkbox("Grid XZ", &engine_p->grid_xz));

            ImGui::Separator();

            if (ImGui::BeginMenu("Draw Mode")) {
                static int selectedOption = 0;

                if (ImGui::RadioButton("Mesh", selectedOption == 0)) {
                    selectedOption = 0;
                    // Code to execute when "Mesh" is selected
                }

                if (ImGui::RadioButton("Wireframe", selectedOption == 1)) {
                    selectedOption = 1;
                    // Code to execute when "Wireframe" is selected
                }

                if (ImGui::RadioButton("Vertex", selectedOption == 2)) {
                    selectedOption = 2;
                    // Code to execute when "Vertex" is selected
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Show")) {
                bool selection_vertexNormals;
                if (ImGui::Checkbox("Vertex Normals", &selection_vertexNormals));          // Temporarly disabled because not implemented (..., false, false)

                bool selection_BoundingBoxes;
                if (ImGui::Checkbox("Bounding Boxes", &selection_BoundingBoxes));          // Temporarly disabled because not implemented (..., false, false)

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("GameObjects")) {

            if (ImGui::MenuItem("Create Empty", NULL, false, false))          // Temporarly disabled because not implemented (..., false, false)
            {
                // Code to execute when "Create Empty" is selected 
            }

            if (ImGui::BeginMenu("3D Object")) {
                if (ImGui::MenuItem("Plane", NULL, false, false))          // Temporarly disabled because not implemented (..., false, false)
                {
                    // Code to execute when "Plane" is selected
                }
                if (ImGui::MenuItem("Cube", NULL, false, false))          // Temporarly disabled because not implemented (..., false, false)
                {
                    // Code to execute when "Cube" is selected
                }
                if (ImGui::MenuItem("Sphere", NULL, false, false))          // Temporarly disabled because not implemented (..., false, false)
                {
                    // Code to execute when "Sphere" is selected
                }

                ImGui::EndMenu();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Align View to Selected", "F", false, false)) {          // Temporarly disabled because not implemented (..., false, false)
                // Code to execute when "Play" is selected
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows")) {
            bool sceneState = true;
            if (app->gui->w_scene->GetWindowState() == States::DISABLED) { sceneState = false; }
            if (ImGui::MenuItem("Scene", NULL, sceneState)) {
                if (app->gui->w_scene->GetWindowState() != States::ENABLED) { app->gui->w_scene->WindowChangeState(States::ENABLED); }
            }

            bool gameState = false;     // Change to true whwn enabled
            //if (app->gui->w_game->GetWindowState() == States::DISABLED) { gameState = false; }
            if (ImGui::MenuItem("Game", NULL, gameState, false)) {          // Temporarly disabled because not implemented (..., false, false)
                //if (app->gui->w_game->GetWindowState() != States::ENABLED) { app->gui->w_game->WindowChangeState(States::ENABLED); }
            }

            bool hierarchyState = true;
            if (app->gui->w_hierarchy->GetWindowState() == States::DISABLED) { hierarchyState = false; }
            if (ImGui::MenuItem("Hierarchy", NULL, hierarchyState)) {
                if (app->gui->w_hierarchy->GetWindowState() != States::ENABLED) { app->gui->w_hierarchy->WindowChangeState(States::ENABLED); }
            }

            bool inspectorState = true;
            if (app->gui->w_inspector->GetWindowState() == States::DISABLED) { inspectorState = false; }
            if (ImGui::MenuItem("Inspector", NULL, inspectorState)) {
                if (app->gui->w_inspector->GetWindowState() != States::ENABLED) { app->gui->w_inspector->WindowChangeState(States::ENABLED); }
            }

            bool projectState = true;
            if (app->gui->w_project->GetWindowState() == States::DISABLED) { projectState = false; }
            if (ImGui::MenuItem("Project", NULL, projectState)) {
                if (app->gui->w_project->GetWindowState() != States::ENABLED) { app->gui->w_project->WindowChangeState(States::ENABLED); }
            }

            bool consoleState = true;
            if (app->gui->w_console->GetWindowState() == States::DISABLED) { consoleState = false; }
            if (ImGui::MenuItem("Console", NULL, consoleState)) {
                if (app->gui->w_console->GetWindowState() != States::ENABLED) { app->gui->w_console->WindowChangeState(States::ENABLED); }
            }            

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help")) {
            if (ImGui::Button("About D. Game Engine")) {
                ImGui::OpenPopup("About this engine...");
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Development Webpage", NULL, false, false))          // Temporarly disabled because not implemented (..., false, false)
                app->RequestBrowser("https://github.com/CITM-UPC/DGameMaker/wiki");

            if (ImGui::MenuItem("Download Latest Version", NULL, false, false))          // Temporarly disabled because not implemented (..., false, false)
                app->RequestBrowser("https://github.com/CITM-UPC/DGameMaker/releases");

            ImGui::Separator();

            if (ImGui::MenuItem("Report Bug || Suggest Feature"))
                app->RequestBrowser("https://github.com/CITM-UPC/DGameMaker/issues");

            if (ImGui::MenuItem("This Engine's GITHUB repository"))
                app->RequestBrowser("https://github.com/CITM-UPC/DGameMaker");



            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    return true;
}