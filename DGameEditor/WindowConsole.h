#pragma once
#include "GUI_Window.h"
class WindowConsole : public GUI_Window
{
public:
	WindowConsole(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();
};