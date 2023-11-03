#pragma once
#include "GUI_Window.h"
class WindowSettings : public GUI_Window
{
public:
	WindowSettings(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();
};

