#pragma once

#include "EditorGlobals.h"

enum States
{
	DISABLED,
	ENABLED,
};

class Module
{
public:
	Module(bool startEnabled = false) : name(""){
		if (startEnabled) { this->state = States::ENABLED; }
		else if (!startEnabled) { this->state = States::DISABLED; }
	}

	~Module() {}

	// Called once at the start of the execution (previous to the existence of the render)
	virtual void Awake() {}

	// Called evry time the module gets enabled
	virtual void Start() {}

	// Called each loop iteration (first in execution)
	virtual void PreUpdate() {}

	// Called each loop iteration (second in execution)
	virtual void Update() {}

	// Called each loop iteration (third in execution)
	virtual void PostUpdate() {}

	// Called to clean the module before quiting or when it gets disabled
	virtual void CleanUp() {}

	void Enable() {
		if (state != States::ENABLED) {
			state = States::ENABLED;
			this->Start();
		}
	}

	void Disable() {
		if (state != States::DISABLED) {
			state = States::DISABLED;
			this->CleanUp();
		}
	}

	States GetState() {
		return state;
	}

public:
	string name;

private:
	States state;
};