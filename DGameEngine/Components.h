#pragma once
#include "GraphicObject.h"
#include "EngineGlobals.h"

enum Ctype {
	NONE,
	COMPONENT_TRANSFORM,
	COMPONENT_MESH,
	COMPONENT_MATERIAL
};

class Components {

public:
	Components(Ctype type) : component_type(type), isActive(true) {}

	//unique_ptr<GraphicObject> graphicObject;

public:
	virtual void Enable() = 0;
	virtual void update() = 0;
	virtual void Disable() = 0;

	void SetActive() { isActive = true; }
	void SetDisable() { isActive = false; }
	bool GetActive() { return isActive; }

	void SetName(string n) { name = n; }
	string GetName() { return name; }

public:
	Ctype component_type = NONE;
	bool isActive;
	string name;
};
