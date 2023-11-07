#pragma once
#include "GraphicObject.h"
#include "EngineGlobals.h"

enum Ctype {
	NONE,
	COMPONENT_TRANSFORM,
	COMPONENT_MESTH,
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

private:
	Ctype component_type = NONE;
	bool isActive;
};
