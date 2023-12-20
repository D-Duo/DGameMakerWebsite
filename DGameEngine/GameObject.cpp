#include <memory>
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"

GameObject::GameObject() {
	name = "";
	AddComponent(Component::TRANSFORM);
}

void GameObject::UpdateGameObj() {

	if (!this->isActive) { return; }

	// Save current position
	glPushMatrix();

	for (const auto& components : components)
	{
		if (components) components->update();
	}

	// Unbind any active shader
	glUseProgram(0);

	// Update for tree structure
	for (const auto& child : children)
	{
		if (child) child->UpdateGameObj();
	}

	// Load last position
	glPopMatrix();
}

void GameObject::AddComponent(Component::Type component) {
	std::unique_ptr<Component> ptr;

	switch (component)
	{
	case Component::Type::TRANSFORM:
		ptr = move(std::make_unique<ComponentTransform>());
		break;
	case Component::Type::MESH:
		ptr = move(std::make_unique<ComponentMesh>());
		break;
	case Component::Type::MATERIAL:
		ptr = move(std::make_unique<ComponentMaterial>());
		break;
	case Component::Type::CAMERA:
		ptr = move(std::make_unique<ComponentCamera>());
		break;
	default:
		cout << "Can't assign wrong component type" << endl;
		break;
	}

	components.push_back(move(ptr));
}

void GameObject::MaterialAddComponent(std::unique_ptr<ComponentMaterial> component) {
	components.push_back(move(component));
}

void GameObject::MeshAddComponent(std::unique_ptr<ComponentMesh> component) {
	components.push_back(move(component));
}

void GameObject::RemoveComponent(unique_ptr<Component> comp) {
	//comp.get_deleter();
}

void GameObject::addChild(unique_ptr<GameObject> child) {
	child->parent = this;
	children.push_back(move(child));
}