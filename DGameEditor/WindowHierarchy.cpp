#include "WindowHierarchy.h"
#include "App.h"
#include <string>

using namespace ImGui;


WindowHierarchy::WindowHierarchy(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowHierarchy::Update() {
	
	if (deleteWindow)
		DeleteWindow();

	counter = 0;
	ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
	for (auto gObj : scene.mGameObjects) {
		ImGuiTreeNodeFlags tmp_flags;

		if (selected == counter)
			tmp_flags = base_flags | ImGuiTreeNodeFlags_Selected;
		else
			tmp_flags = base_flags;

		string name = "	" + gObj->GetName();
		if (TreeNodeEx(name.c_str(), tmp_flags))
			TreePop();

		if (IsItemClicked())
		{
			app->engineManager->GetEngine()->myScene.selectedGobj = gObj;
			selected = counter;
		}
		else if (IsItemClicked(1) && IsWindowHovered()) {
			deleteWindow = true;
			scene.selectedGobj = gObj;
		}
		counter++;
	}
}

void WindowHierarchy::DeleteWindow()
{
	if (IsMouseReleased(0) || IsMouseReleased(2))
		deleteWindow = false;
	else if (IsMouseClicked(1))
		deleteWindow = false;

	OpenPopup("DeleteWindow");
	if (BeginPopup("DeleteWindow"))
	{
		if (MenuItem("Delete"))
		{
			deleteWindow = false;
		}

		EndPopup();
	}
}