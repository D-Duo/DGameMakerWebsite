#pragma once
#include "GUI_Window.h"
class WindowSettings : public GUI_Window
{
public:
	WindowSettings(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void PreUpdate();

	void Update();

	int framerate;

private:
	int selectedResolution;
	int selectedWindowType;
	bool borderless;
	bool vsync;
	float brightnessValue;

	std::vector<float> ut_history;
	std::vector<float> ft_history;
	std::vector<float> fps_history;
};

