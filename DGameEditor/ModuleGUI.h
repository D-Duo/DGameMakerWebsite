#pragma once

#include "Module.h"
#include "GUI_Window.h"

#include "WindowScene.h"
#include "WindowHierarchy.h"
#include "WindowInspector.h"
#include "WindowProject.h"
#include "WindowConsole.h"
#include "WindowSettings.h"

// GUI Windows
class WindowScene;
class WindowHierarchy;
class WindowInspector;
class WindowProject;
class WindowConsole;
class WindowSettings;

class ModuleGUI : public Module
{
public:
	WindowScene* w_scene;
	WindowHierarchy* w_hierarchy;
	WindowInspector* w_inspector;
	WindowProject* w_project;
	WindowConsole* w_console;
	WindowSettings* w_settings;

public:
	ModuleGUI(bool startEnabled);
	~ModuleGUI();

	void Awake();

	void Start();

	bool PreUpdate();

	bool Update(std::chrono::duration<double> dt);

	bool PostUpdate();

	void CleanUp();

	void AddWindow(GUI_Window* window);

private:
	void ImguiInit(SDL_Window* window, SDL_GLContext gl_context);
	
	bool ImguiDockspace();
	void ImguiSetup();

public:
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImFont* font1_body_12;
	ImFont* font1_body_14;
	ImFont* font1_title_18;
	ImFont* font_awesome_title;

private:
	list<GUI_Window*> windows;
};