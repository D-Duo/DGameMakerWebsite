#pragma once
#include "GUI_Window.h"
class WindowHierarchy : public GUI_Window
{
public:
    WindowHierarchy(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

    void Update();
};