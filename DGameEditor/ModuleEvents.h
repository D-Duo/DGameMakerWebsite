#pragma once
#include "Module.h"

#define MAX_MOUSE_BUTTONS 5
#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleEvents : public Module
{
public:
	ModuleEvents(bool startEnabled);
	~ModuleEvents();

	void Awake();

	bool PreUpdate();

private:
	bool SDLEventsProcess();

public:
	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}

	KEY_STATE GetMouseButton(int id) const
	{
		return mouse_buttons[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

	int GetMouseZ() const
	{
		return mouse_z;
	}

	int GetMouseMotionX() const
	{
		return mouse_motion_x;
	}

	int GetMouseMotionY() const
	{
		return mouse_motion_y;
	}

private:
	KEY_STATE* keyboard;
	KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS];
	int mouse_x;
	int mouse_y;
	int mouse_z;
	int mouse_motion_x;
	int mouse_motion_y;
};