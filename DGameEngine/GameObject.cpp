#include <memory>
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

GameObject::GameObject(const string meshPath = "", const string texturePath = "", mat4 transform = glm::identity<mat4>()) {
	shared_ptr<Components> newComp;
	//transform component

	//mesh component
	newComp = CreateComponent(COMPONENT_MESTH, meshPath);
	AddComponent(newComp);

	//texture component
	newComp = CreateComponent(COMPONENT_MATERIAL, texturePath);
	AddComponent(newComp);

}

shared_ptr<Components> GameObject::CreateComponent(Ctype type, const string path) {

	shared_ptr<Components> newComp = nullptr;

	switch (type)
	{
	case Ctype::NONE:
		break;
	case Ctype::COMPONENT_TRANSFORM:
		
		break;
	case Ctype::COMPONENT_MESTH:
		newComp = make_shared<ComponentMesh>(path);
		break;
	case Ctype::COMPONENT_MATERIAL:
		newComp = make_shared<ComponentMaterial>(path);
		break;
	default:
		break;
	}
	return newComp;
}

void GameObject::AddComponent(shared_ptr<Components> comp) {
	gObj_components.push_back(comp);
}

void GameObject::RemoveComponent(shared_ptr<Components> comp) {

}

void GameObject::UpdateGameObj() {
	for (auto components : gObj_components)
	{
		components->update();
	}
}