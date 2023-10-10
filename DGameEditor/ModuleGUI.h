#pragma once

class ModuleGUI {
public:
	ModuleGUI();
	~ModuleGUI()
	{

	}

public:
	void ImguiInit(SDL_Window* window, SDL_GLContext gl_context);

	void ImguiExample();

	void ImguiCleanUp();

public:
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
private:

	bool show_demo_window = true;
	bool show_another_window = false;
};