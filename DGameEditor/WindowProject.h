#pragma once
#include "GUI_Window.h"
class WindowProject : public GUI_Window
{
public:
	WindowProject(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();
};