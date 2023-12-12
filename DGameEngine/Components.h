#pragma once
#include "GraphicObject.h"
#include "EngineGlobals.h"

class GameObject;

class Component {

public:
	enum Type {
		NONE,
		TRANSFORM,
		MESH,
		MATERIAL,
		CAMERA
	};

	Component(GameObject& owner) : owner(owner), isActive(true) {}

	virtual void update() = 0;
	virtual Type getType() const = 0;

	void SetActive() { isActive = true; }
	void Disable() { isActive = false; }

	GameObject& owner;

	void SetName(string n) { name = n; }
	string GetName() { return name; }

public:
	bool isActive;
	string name;
};
