#pragma once

#include "Components.h"
#include "EngineGlobals.h"
#include "Graphic.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(const string, const string texturePath, mat4 transform);
	//GameObject(std::shared_ptr<Graphic> graphic);

	shared_ptr<Components> CreateComponent(Ctype type, const string path);

	bool isActive;
	string name;
	vector<shared_ptr<Components>> gObj_components;

public:
	void AddComponent(shared_ptr<Components> comp);
	void RemoveComponent(shared_ptr<Components> comp);
	void UpdateGameObj();

};

