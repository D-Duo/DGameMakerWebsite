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

public:
	template <typename T> T* GetComponent();

	void AddComponent(Component::Type component);
	void MaterialAddComponent(std::shared_ptr<ComponentMaterial> component);
	void MeshAddComponent(std::shared_ptr<ComponentMesh> component);
	void RemoveComponent(shared_ptr<Component> comp);
	void UpdateGameObj();

public:
	void SetActive() { isActive != isActive; }
	void SetUnactive() { isActive = false; }
	void SetName(string n) { name = n; }

	string GetName() { return name; }
	bool GetIsActive() { return isActive; }

private:
	string name;

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