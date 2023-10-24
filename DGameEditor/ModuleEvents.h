#pragma once
#include "Module.h"

class ModuleEvents : public Module
{
public:
	ModuleEvents();
	~ModuleEvents();

	static bool SDLEventsProcess();

private:

};