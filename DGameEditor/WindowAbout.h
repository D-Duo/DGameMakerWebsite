#pragma once
#include "GUI_Window.h"
class WindowAbout : public GUI_Window
{
public:
	WindowAbout(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void PreUpdate();

	void Update();
};