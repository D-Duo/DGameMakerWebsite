#pragma once
#include "GUI_Window.h"
#include "App.h"

#include "ComponentMesh.h"
#include "ComponentMaterial.h"

#define scene app->engineManager->GetEngine()->myScene

class WindowInspector : public GUI_Window
{
public:
	WindowInspector(string name, bool startEnabled = false, ImGuiWindowFlags flags = ImGuiWindowFlags_None);

	void Update();

	void DrawComponentMesh(shared_ptr<ComponentMesh> cMesh);

	void DrawComponentMaterial(shared_ptr<ComponentMaterial> cMaterial);

	void DrawComponentTransform();

	char buffer[256] = "";
};

