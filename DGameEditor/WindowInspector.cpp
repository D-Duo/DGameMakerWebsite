#define _CRT_SECURE_NO_WARNINGS

#include "WindowInspector.h"
#include <cstring>


using namespace ImGui;

WindowInspector::WindowInspector(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowInspector::Update() {

	//shared_ptr<GameObject> gObj = app->engineManager->sel_GameObject.gameObject;

	//if (gObj != nullptr)
	//{

	//	AlignTextToFramePadding();

	//	bool ifActive = gObj->GetIsActive();
	//	if (Checkbox("Active", &ifActive));

	//	if (ifActive) {
	//		app->engineManager->sel_GameObject.gameObject->SetActive();
	//	}
	//	else
	//	{
	//		app->engineManager->sel_GameObject.gameObject->SetUnactive();
	//	}
	//	


	//	SameLine();
	//	
	//	string name = gObj->GetName().c_str();
	//	strcpy(buffer, name.c_str());
	//	SetNextItemWidth(GetWindowWidth() / 3.0f);
	//	if (InputText("##EditableText", buffer, IM_ARRAYSIZE(buffer)))
	//	{
	//		string newName(buffer);
	//		app->engineManager->sel_GameObject.gameObject->SetName(newName);
	//	}
	//	
	//	SameLine();

	//	bool toDelete = true;
	//	Checkbox("Static", &toDelete);

	//	Separator();

	//		//shared_ptr<Component> comp = gObj->GetComponent(COMPONENT_MESH);
	//	shared_ptr<ComponentMesh> compMesh = *gObj->GetComponent<shared_ptr<ComponentMesh>>();
	//	//shared_ptr<ComponentMesh> compMesh = dynamic_pointer_cast<ComponentMesh>(comp);

	//	DrawComponentTransform();

	//	DrawComponentMesh(compMesh);

	//	shared_ptr<ComponentMaterial> compMaterial = *gObj->GetComponent<shared_ptr<ComponentMaterial>>();
	//	//shared_ptr<ComponentMaterial> compMaterial = dynamic_pointer_cast<ComponentMaterial>(comp);

	//	DrawComponentMaterial(compMaterial);
	//}
}

void WindowInspector::DrawComponentTransform() {

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

void WindowInspector::DrawComponentMesh(shared_ptr<ComponentMesh> cMesh) {

	ImGuiTreeNodeFlags imFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

	Text("");
	Separator();

	if (TreeNodeEx("Mesh", imFlags))
	{
		Columns(2);
		Separator();
		AlignTextToFramePadding();

		Checkbox("Active", &cMesh->isActive);

		NextColumn();

		Text("File:"); SameLine(); TextColored(ImVec4(0.0f, 255.0f, 255.0f, 255.0f), cMesh->mesh->path.c_str());

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

void WindowInspector::DrawComponentMaterial(shared_ptr<ComponentMaterial> cMaterial) {

	ImGuiTreeNodeFlags imFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

	Text("");
	Separator();

	if (TreeNodeEx("Material", imFlags))
	{
		Separator();

		Checkbox("Active", &cMaterial->isActive);

		Text("File"); SameLine(); TextColored(ImVec4(255.0f, 255.0f, 0.0f, 255.0f), cMaterial->texture->path.c_str());
	}
	Separator();
}