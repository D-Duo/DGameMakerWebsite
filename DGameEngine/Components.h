#pragma once
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

	Component() : isActive(true) {}
	Component(Component&& c) noexcept : 
		isActive(c.isActive), 
		name(c.name) 
	{}

	virtual void update() = 0;
	virtual Type getType() const = 0;

	void SetActive() { isActive = true; }
	void Disable() { isActive = false; }
	bool GetIsActive() { return isActive; }

	void SetName(string n) { name = n; }
	string GetName() { return name; }

private:
	bool isActive;
	string name;
};
