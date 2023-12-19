#pragma once
#include "GUI_Window.h"
#include "App.h"

#include "ComponentMesh.h"
#include "ComponentMaterial.h"

class WindowInspector : public GUI_Window
{
public:
	WindowInspector(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();

	void DrawComponentMesh(ComponentMesh* cMesh);

	void DrawComponentMaterial(ComponentMaterial* cMaterial);

	void DrawComponentTransform();

	char buffer[256] = "";
};

