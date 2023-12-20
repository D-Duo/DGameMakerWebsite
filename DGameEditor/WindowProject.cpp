#include "WindowProject.h"

//#include "SDL2/SDL.h";
//#include "SDL2/SDL"

#include <Windows.h>
#include <iostream>
#include <string>

using namespace ImGui;
using namespace std;

WindowProject::WindowProject(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) { 

    //GLuint imageIcon = LoadTextureFromFile("Assets/UI/imageIcon.png");
    //GLuint fontIcon = LoadTextureFromFile("Assets/UI/fontIcon.png");
    //GLuint fbxIcon = LoadTextureFromFile("Assets/UI/fbxIcon.png");
    //GLuint comingSoonIcon = LoadTextureFromFile("Assets/UI/comingSoonIcon.png");
    //GLuint folderIcon = LoadTextureFromFile("Assets/UI/folderIcon.png");
    
};

void WindowProject::Update() {

    counter = 0;

    ImGui::Columns(2);

    int colWidth = GetWindowWidth() * 0.2;
    colWidth = colWidth < minTreeColumnWidth ? minTreeColumnWidth : colWidth;
    ImGui::SetColumnWidth(-1, colWidth);

    //1st Column
    ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
    
    ShowLibraryTree(directoryPath, counter, base_flags);

    ImGui::NextColumn();

    //2nd Column

    if (selectedPath != "")
    {
        ShowLibraryFiles(selectedPath, GetNumFiles(selectedPath));
    }   
}

void WindowProject::ShowLibraryTree(const fs::path& rootDirectory, int counter, ImGuiTreeNodeFlags bFlags) {

    if (IsLibrary(rootDirectory))
    {
        for (const auto& item : fs::directory_iterator(rootDirectory)) {

            if (IsLibrary(item.path()))
            {
                counter++;

                ImGuiTreeNodeFlags tmp_flags = bFlags;

                if (selected == counter)
                {
                    tmp_flags |= ImGuiTreeNodeFlags_Selected;
                }
                if (!fs::is_directory(item))
                {
                    tmp_flags |= ImGuiTreeNodeFlags_Leaf;
                }

                bool open_tree = TreeNodeEx((void*)(intptr_t)counter, tmp_flags, "%s", item.path().filename().string().c_str());

                if (open_tree) {

                    if (IsItemClicked(0))
                    {
                        selected = counter;
                        selectedPath = item.path();
                    }
                    else if (IsItemClicked(1) && IsWindowHovered())
                    {

                    }

                    if (fs::is_directory(item)) {
                        ShowLibraryTree(item.path().c_str(), counter, bFlags);
                    }
                    TreePop();
                }
            }
        }
    }
}

void WindowProject::ShowLibraryFiles(fs::path& sPath, int numFiles) {
    int counter = 0;
    if (BeginTable(selectedPath.string().c_str(), numFiles)) {
        TableSetupColumn(sPath.string().c_str());
    
        // Table data
        for (const auto& item : fs::directory_iterator(sPath)) {
            TableNextColumn();
            Text("%s", item.path().filename().string().c_str());
            counter++;
            if (counter == 6)
            {
                TableNextRow();
            }
        }
    
        EndTable();
    }
}

bool WindowProject::HasFilesInDirectory(const fs::path& directoryPath) {
    
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            return true;
        }
    }
    return false;
}

bool WindowProject::IsLibrary(const fs::path& directoryPath) {

    string filePath = directoryPath.filename().string();
    if (filePath != "")
    {
        if (filePath.find(".") != std::string::npos)
        {
            return false;
        }
    }       
    return true;
}

int WindowProject::GetNumFiles(const fs::path& directoryPath) {

    int counter = 0;

    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        if (fs::is_regular_file(entry)) {
            counter++;
        }
    }
    return counter;
}

SDL_Texture* WindowProject::LoadTextureFromFile(const fs::path& textPath) {

    //SDL_Texture* texture = NULL;
    //SDL_Surface* surface = IMG_Load(path);
    //
    //if (surface == NULL)
    //{
    //    LOG("Could not load surface with path: %s. IMG_Load: %s", path, IMG_GetError());
    //}
    //else
    //{
    //    texture = LoadSurface(surface);
    //    SDL_FreeSurface(surface);
    //}
    //
    //return texture;
    return nullptr;
}

std::vector<std::string> GetFilesAndDirs(const std::string& directory) {
    std::vector<std::string> filesAndDirs;

    for (const auto& entry : fs::directory_iterator(directory)) {
        filesAndDirs.push_back(entry.path().string());
    }

    return filesAndDirs;
}

bool IsDirectory(const std::string& path) {
    return fs::is_directory(path);
}

