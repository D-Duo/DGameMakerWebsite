#pragma once
#include "GUI_Window.h"
#include "App.h"

//#define scene app->engineManager->GetEngine()->myScene

class WindowHierarchy : public GUI_Window
{
public:
    WindowHierarchy(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

    void Update();
    void RenderGameObjectTree(const unique_ptr<GameObject>& gObj, int& counter, int& selected, ImGuiTreeNodeFlags bFlags);
    void DeleteWindow();

    bool itemSelected = false;
    int selected = 0;
    int counter = 0;
    bool deleteWindow = false;
};