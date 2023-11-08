#pragma once

#include "Components.h"
#include "EngineGlobals.h"
#include "Graphic.h"

class Mesh;
class Texture2D;

class GameObject
{
public:
	GameObject() = default;
	GameObject(const string, const string texturePath, mat4 transform);

	vector<shared_ptr<Components>> gObj_components;

public:
	shared_ptr<Components> CreateComponent(Ctype type, shared_ptr<Mesh>&& mesh, shared_ptr<Texture2D>&& texture);
	shared_ptr<Components> GetComponent(Ctype type);

	void AddComponent(shared_ptr<Components> comp);
	void RemoveComponent(shared_ptr<Components> comp);
	void UpdateGameObj();

public:
	bool isActive;
	string name;
	int tag;

public:
	void SetActive() { isActive != isActive; }
	void SetUnactive() { isActive = false; }
	bool& GetActive() { return isActive; }

	void SetName(string n) { name = n; }
	string GetName() { return name; }

	void SetTag(int t) { tag = t; }
	int GetTag() { return tag; }

};

