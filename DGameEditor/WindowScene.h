#pragma once
#include "GUI_Window.h"
#include "FrameBuffer.h"

class WindowScene : public GUI_Window
{
public:
	WindowScene(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();

	FrameBuffer SceneFBO;
};