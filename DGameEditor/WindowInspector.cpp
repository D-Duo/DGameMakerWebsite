#define _CRT_SECURE_NO_WARNINGS

#include "WindowInspector.h"
#include "ComponentTransform.h"
#include <cstring>


using namespace ImGui;

WindowInspector::WindowInspector(string name, bool startEnabled, ImGuiWindowFlags flags) : GUI_Window(name, startEnabled, flags) {};

void WindowInspector::Update() {

	if (app->engineManager->sel_GameObject.gameObject != nullptr)
	{
		auto gObj = app->engineManager->sel_GameObject.gameObject;

		AlignTextToFramePadding();
			
		bool active = gObj->GetIsActive();
		Checkbox("Active", &active);
		if (!active) {
			gObj->SetUnactive();
		}
		else {
			gObj->SetActive();
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

		bool toDelete = false;
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

		NextColumn(); Text("X"); NextColumn(); Text("Y"); NextColumn(); Text("Z"); Separator();

		NextColumn();

		bool need_refresh_pos = false;
		bool need_refresh_rot = false;
		bool need_refresh_scale = false;

		auto pos = app->engineManager->sel_GameObject.gameObject->GetComponent<ComponentTransform>()->extractTranslation();
		AlignTextToFramePadding();
		Text("Position"); NextColumn();
		float temp = pos.x;
		if (DragFloat("##PX", &temp, 0.5F, 0, 0, "%.3f")) {
			need_refresh_pos = true;
			pos.x = temp;
		}
		NextColumn();
		
		temp = pos.y;
		if (DragFloat("##PY", &temp, 0.5F, 0, 0, "%.3f")) {
			need_refresh_pos = true;
			pos.y = temp;
		}
		NextColumn();
		
		temp = pos.z;
		if (DragFloat("##PZ", &temp, 0.5F, 0, 0, "%.3f")) {
			need_refresh_pos = true;
			pos.z = temp;
		}
		NextColumn();		

		if (need_refresh_pos) {
			app->engineManager->sel_GameObject.gameObject->GetComponent<ComponentTransform>()->setPosition(pos);
		}

		auto rot = app->engineManager->sel_GameObject.gameObject->GetComponent<ComponentTransform>()->extractRotationEuler();
		AlignTextToFramePadding();
		Text("Rotation"); NextColumn();
		temp = rot.x;
		if (DragFloat("##RX", &temp, 0.5F, 0, 0, "%.3f")) {
			need_refresh_rot = true;
			rot.x = temp;
		}
		NextColumn();
		
		temp = rot.y;
		if (DragFloat("##RY", &temp, 0.5F, 0, 0, "%.3f")) {
			need_refresh_rot = true;
			rot.y = temp;
		}
		NextColumn();
		
		temp = rot.z;
		if (DragFloat("##RZ", &temp, 0.5F, 0, 0, "%.3f")) {
			need_refresh_rot = true;
			rot.z = temp;
		}
		NextColumn();		

		if (need_refresh_rot) {
			app->engineManager->sel_GameObject.gameObject->GetComponent<ComponentTransform>()->setRotation(rot, ComponentTransform::Space::GLOBAL);
		}

		auto sc = app->engineManager->sel_GameObject.gameObject->GetComponent<ComponentTransform>()->extractScale();
		AlignTextToFramePadding();
		Text("Scale"); NextColumn();
		temp = sc.x;
		if(DragFloat("##SX", &temp, 0.5F, 0, 0, "%.3f")){
			need_refresh_scale = true;
			sc.x = temp;
		}
		NextColumn();
		
		temp = sc.y;
		if(DragFloat("##SY", &temp, 0.5F, 0, 0, "%.3f")){
			need_refresh_scale = true;
			sc.y = temp;
		}
		NextColumn();
		
		temp = sc.z;
		if(DragFloat("##SZ", &temp, 0.5F, 0, 0, "%.3f")){
			need_refresh_scale = true;
			sc.z = temp;
		}
		NextColumn();		
		
		if (need_refresh_scale) {
			app->engineManager->sel_GameObject.gameObject->GetComponent<ComponentTransform>()->setScale(sc);
		}

	}
	Columns(1);
	Separator();
}

void WindowInspector::DrawComponentMesh(ComponentMesh* cMesh) {

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
			Checkbox("Active", &active);
			if (!active) {
				cMesh->Disable();
			}
			else {
				cMesh->SetActive();
			}

			NextColumn();

			//Text("File:"); SameLine(); TextColored(ImVec4(0.0f, 255.0f, 255.0f, 255.0f), cMesh->mesh->path.c_str());

			Separator();
			NextColumn();

			Text("Draw:");
			bool toDelete = false; //will be deleted 
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