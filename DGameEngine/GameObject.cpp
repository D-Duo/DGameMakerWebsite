#include "GameObject.h"
#include "Mesh.h"
#include <memory>

GameObject::GameObject(const string meshPath = "", const string texturePath = "", mat4 transform = glm::identity<mat4>()) {
	shared_ptr<Components> newComp;
	//for transform
	newComp = CreateComponent(COMPONENT_MESTH, meshPath);
	AddComponent(newComp);
	//for texture

}

shared_ptr<Components> GameObject::CreateComponent(Ctype type, const string path) {

	shared_ptr<Components> newComp;

	switch (type)
	{
	case Ctype::NONE:
		break;
	case Ctype::COMPONENT_TRANSFORM:
		
		break;
	case Ctype::COMPONENT_MESTH:
		newComp = make_shared<Mesh>(path);
		break;
	case Ctype::COMPONENT_MATERIAL:
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