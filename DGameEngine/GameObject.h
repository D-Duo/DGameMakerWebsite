#pragma once

#include "Components.h"
#include "EngineGlobals.h"
#include "Graphic.h"

#include "ComponentMaterial.h"
#include "ComponentMesh.h"

class ComponentMesh;
class ComponentMaterial;

class GameObject
{
public:
	GameObject();

	string name;

public:
	template <typename T> T* GetComponent();

	void AddComponent(Component::Type component);
	void MaterialAddComponent(std::shared_ptr<ComponentMaterial> component);
	void MeshAddComponent(std::shared_ptr<ComponentMesh> component);
	void RemoveComponent(shared_ptr<Component> comp);
	void UpdateGameObj();

	void SetActive() { isActive = true; }
	void SetUnactive() { isActive = false; }

private:
	bool isActive;
	vector<shared_ptr<Component>> components;
};

template<typename T>
inline T* GameObject::GetComponent()
{
	for (auto component : components) {
		T* returnComponent = dynamic_cast<T*>(component.get());
		if (returnComponent) {
			return returnComponent;
		}
	}
	return nullptr;
}