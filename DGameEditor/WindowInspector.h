#pragma once
#include "GUI_Window.h"
class WindowInspector : public GUI_Window
{
public:
	WindowInspector(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();
};

