#include "WindowHierarchy.h"
#include "App.h"
#include <string>

using namespace ImGui;

WindowHierarchy::WindowHierarchy(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowHierarchy::RenderGameObjectTree(const unique_ptr<GameObject>& gObj, int& counter, int& selected, ImGuiTreeNodeFlags bFlags)
{
    string name = "	" + gObj->GetName();

    ImGuiTreeNodeFlags tmp_flags = bFlags;
    //ImGuiTreeNodeFlags tmp_flags = (selected == counter) ? ImGuiTreeNodeFlags_Selected : base_flags;
   
    //flags setting
    if (selected == counter)
    {
        tmp_flags |= ImGuiTreeNodeFlags_Selected;
    }
    if (gObj->GetChildren().empty())
    {
        tmp_flags |= ImGuiTreeNodeFlags_Leaf;
    }
    if (selected == counter)//gObj->GetSelected())
    {
        tmp_flags |= ImGuiTreeNodeFlags_Selected;
    }

    //ImGuiTreeNodeFlags_Bullet
    if (TreeNodeEx(name.c_str(), tmp_flags))
    {
        if (IsItemClicked(0))
        {
            app->engineManager->sel_GameObject.gameObject = gObj.get();
            selected = counter;
            //gObj->SetSelected();
        }
        else if (IsItemClicked(1) && IsWindowHovered())
        {
            //Handle right-click
            deleteWindow = true;
            app->engineManager->sel_GameObject.gameObject = gObj.get();
        }

        for (const auto& child : gObj->GetChildren())
        {
            counter++;
            // Recursively render child objects
            RenderGameObjectTree(child, counter, selected, bFlags);
        }
        TreePop();
    }
}

void WindowHierarchy::Update()
{
    if (deleteWindow)
        DeleteWindow();

    counter = 0;

    ImGuiTreeNodeFlags base_flags =  ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

    for (const auto& gObj : app->engineManager->sel_Scene.scene->gameObjects)
    {
        counter++;
        RenderGameObjectTree(gObj, counter, selected, base_flags);
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