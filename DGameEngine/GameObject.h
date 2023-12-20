#pragma once

#include "Components.h"
#include "EngineGlobals.h"
#include "Graphic.h"

#include "ComponentMaterial.h"
#include "ComponentMesh.h"

class ComponentMesh;
class ComponentMaterial;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	GameObject(GameObject&& g) noexcept :
		isActive(g.isActive),
		name(g.name),
		components(move(g.components))
	{}

public:

	void UpdateGameObj();

	//components
	template <typename T> T* GetComponent();
	void AddComponent(Component::Type component);
	void MaterialAddComponent(std::unique_ptr<ComponentMaterial> component);
	void MeshAddComponent(std::unique_ptr<ComponentMesh> component);
	void RemoveComponent(unique_ptr<Component> comp);

	//tree
	void addChild(unique_ptr<GameObject> child);

public:
	void SetActive() { isActive = true; }
	void SetUnactive() { isActive = false; }
	void SetName(string n) { name = n; }
	void SetIndex(int i) { index = i; }

	string GetName() { return name; }
	string GetUUID() { return UUID; }
	int GetIndex() { return index; }
	bool GetIsActive() { return isActive; }
	GameObject& GetParent() { return *parent; }
	vector<unique_ptr<GameObject>>& GetChildren() { return children; }

private:

	//void CreateUUID();

	string name;
	string UUID;
	int index;
	bool isActive;
	GameObject* parent;
	vector<unique_ptr<GameObject>> children;

	//vector<shared_ptr<Component>> components;
	vector<unique_ptr<Component>> components;

private:
	GameObject(const GameObject& cpy) = delete;
	GameObject& operator=(const GameObject&) = delete;
};

template<typename T>
inline T* GameObject::GetComponent()
{
	for (auto& component : components) {
		T* returnComponent = dynamic_cast<T*>(component.get());
		if (returnComponent) {
			return returnComponent;
		}
	}
	return nullptr;
}