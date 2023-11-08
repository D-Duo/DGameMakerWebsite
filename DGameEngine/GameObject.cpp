#include <memory>
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

GameObject::GameObject(const string meshPath = "", const string texturePath = "", mat4 transform = glm::identity<mat4>()) {
	shared_ptr<Components> newComp;
	//transform component

	//mesh component
	//newComp = CreateComponent(COMPONENT_MESTH, meshPath);
	//AddComponent(newComp);

	////texture component
	//newComp = CreateComponent(COMPONENT_MATERIAL, texturePath);
	//AddComponent(newComp);

}

shared_ptr<Components> GameObject::CreateComponent(Ctype type, shared_ptr<Mesh>&& mesh, shared_ptr<Texture2D>&& texture) {

	shared_ptr<Components> newComp = nullptr;

	switch (type)
	{
	case Ctype::NONE:
		break;
	case Ctype::COMPONENT_TRANSFORM:
		
		break;
	case Ctype::COMPONENT_MESH:
		newComp = make_shared<ComponentMesh>(move(mesh));
		newComp->component_type = COMPONENT_MESH;
		break;
	case Ctype::COMPONENT_MATERIAL:
		newComp = make_shared<ComponentMaterial>(move(texture));
		newComp->component_type = COMPONENT_MATERIAL;
		break;
	default:
		break;
	}
	return newComp;
}

shared_ptr<Components> GameObject::GetComponent(Ctype type) {
	for (auto comp : gObj_components) {
		if (comp->component_type == type) {
			return comp;
		}
	}
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