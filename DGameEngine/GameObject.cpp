#include <memory>
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

GameObject::GameObject() {
	name = "";
	//components.push_back(make_shared<ComponentTransform>(*this));
}

void GameObject::AddComponent(Component::Type component) {
	std::shared_ptr<Component> ptr;

	switch (component)
	{
	case Component::Type::TRANSFORM:
		//ptr = std::make_shared<Transform>(*this);
		break;
	case Component::Type::MESH:
		ptr = std::make_shared<ComponentMesh>(*this);
		break;
	case Component::Type::MATERIAL:
		ptr = std::make_shared<ComponentMaterial>(*this);
		break;
	case Component::Type::CAMERA:
		//ptr = std::make_shared<Camera>(*this);
		break;
	default:
		cout << "Can't assign wrong component type" << endl;
		break;
	}

	components.push_back(ptr);
}

void GameObject::MaterialAddComponent(std::shared_ptr<ComponentMaterial> component) {
	component->owner = *this;
	components.push_back(component);
}

void GameObject::MeshAddComponent(std::shared_ptr<ComponentMesh> component) {
	component->owner = *this;
	components.push_back(component);
}

void GameObject::RemoveComponent(shared_ptr<Component> comp) {

}

void GameObject::UpdateGameObj() {
	for (auto components : components)
	{
		components->update();
	}
}