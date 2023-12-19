#define _CRT_SECURE_NO_WARNINGS

#include "WindowInspector.h"
#include <cstring>


using namespace ImGui;

WindowInspector::WindowInspector(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowInspector::Update() {

	auto gObj = app->engineManager->sel_GameObject.gameObject;

	if (gObj != nullptr)
	{

		AlignTextToFramePadding();

		bool ifActive = gObj->GetIsActive();
		if (Checkbox("Active", &ifActive));

		if (ifActive) {
			gObj->SetActive();
		}
		else
		{
			gObj->SetUnactive();
		}

		SameLine();
		
		string name = gObj->GetName().c_str();
		strcpy(buffer, name.c_str());
		SetNextItemWidth(GetWindowWidth() / 3.0f);
		if (InputText("##EditableText", buffer, IM_ARRAYSIZE(buffer)))
		{
			string newName(buffer);
			app->engineManager->sel_GameObject.gameObject->SetName(newName);
		}
		
		SameLine();

		bool toDelete = true;
		Checkbox("Static", &toDelete);

		Separator();

		DrawComponentTransform();

		auto cMesh = gObj->GetComponent<ComponentMesh>();
		DrawComponentMesh(cMesh);

		auto cMaterial = gObj->GetComponent<ComponentMaterial>();
		DrawComponentMaterial(cMaterial);
	}
}

void WindowInspector::DrawComponentTransform() {

	//auto compTransform = app->engineManager->sel_Scene.scene->gameObjects[currentIndex]->GetComponent<ComponentTransform>();

	ImGuiTreeNodeFlags imFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

	Text("");
	Separator();

	if (TreeNodeEx("Transform", imFlags))
	{
		Columns(4);
		Separator();
		
		bool toDelete = true;	//will be deleted 
		Checkbox("Active", &toDelete); NextColumn(); Text("X"); NextColumn(); Text("Y"); NextColumn(); Text("Z"); Separator();

		NextColumn();

		float tempValue = 0.000f; //will be deleted
		AlignTextToFramePadding();
		Text("Position"); NextColumn(); 
		DragFloat("##PX", &tempValue, 0.005f); NextColumn(); 
		DragFloat("##PY", &tempValue, 0.005f);  NextColumn(); 
		DragFloat("##PZ", &tempValue, 0.005f); NextColumn();

		AlignTextToFramePadding();
		Text("Rotation"); NextColumn(); 
		DragFloat("##RX", &tempValue, 0.005f); NextColumn();
		DragFloat("##RY", &tempValue, 0.005f);  NextColumn();
		DragFloat("##RZ", &tempValue, 0.005f); NextColumn();

		AlignTextToFramePadding();
		Text("Scale"); NextColumn();
		DragFloat("##SX", &tempValue, 0.005f); NextColumn();
		DragFloat("##SY", &tempValue, 0.005f);  NextColumn();
		DragFloat("##SZ", &tempValue, 0.005f); NextColumn();

	}
	Columns(1);
	Separator();
}

void WindowInspector::DrawComponentMesh(ComponentMesh* cMesh) {

	//auto cMesh = app->engineManager->sel_Scene.scene->gameObjects[currentIndex]->GetComponent<ComponentMesh>();

	if (cMesh)
	{
		ImGuiTreeNodeFlags imFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

		Text("");
		Separator();

		if (TreeNodeEx("Mesh", imFlags))
		{
			Columns(2);
			Separator();
			AlignTextToFramePadding();

			bool active = cMesh->GetIsActive();
			//Checkbox("Active", &cMesh->isActive);
			Checkbox("Active", &active);

			NextColumn();

			//Text("File:"); SameLine(); TextColored(ImVec4(0.0f, 255.0f, 255.0f, 255.0f), cMesh->mesh->path.c_str());

			Separator();
			NextColumn();

			Text("Draw:");
			bool toDelete = true; //will be deleted 
			Checkbox("Vertex Normals", &toDelete);
			Checkbox("Face Normals", &toDelete); //SameLine(200);

			NextColumn();

			Text("Indexes:"); SameLine(); Text("%u", cMesh->mesh->GetNumIndex());
			Text("Normals:"); SameLine(); Text("%u", 0);
			Text("Vertexs:"); SameLine(); Text("%u", cMesh->mesh->GetNumVerts());
			Text("Faces:"); SameLine(); Text("%u", 0);
			Text("Tex Coords:"); SameLine(); Text("%u", 0);

			TreePop();
		}
		Columns(1);
		Separator();
	}
}

void WindowInspector::DrawComponentMaterial(ComponentMaterial* cMaterial) {

	//auto cMaterial = app->engineManager->sel_Scene.scene->gameObjects[currentIndex]->GetComponent<ComponentMaterial>();

	if (cMaterial != nullptr)
	{
		ImGuiTreeNodeFlags imFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

	Text("");
	Separator();

	if (TreeNodeEx("Material", imFlags))
	{
		Separator();

		bool active = cMaterial->GetIsActive();
		Checkbox("Active", &active);

		Text("File"); SameLine(); TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.0f), cMaterial->texture->path.c_str());
	}
	Separator();
	}
}