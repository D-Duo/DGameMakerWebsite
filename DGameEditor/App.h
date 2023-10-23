#pragma once

#include "EditorGlobals.h"
#include "Module.h"

using namespace chrono;

// Modules Classes

class App
{
public:
	// Modules


private:
	int argc;
	char** args;

	list<Module*> modules;

	// FPS control
	double dt, previousTime, targetFrameTime;
	double frameRate = 60.0; // 60 frames per second

public:
	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	void Awake();

	// Called before the first frame
	void Start();

	// Called each loop iteration and returns false if wants to stop execution
	bool DoUpdate();

	// Called before quitting
	void CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);


	// FPS control
	void ChangeFramerate(double newFrameRate) {
		this->targetFrameTime = 1.0 / newFrameRate;
	}

	double GetDeltaTime() {
		return dt;
	}

	double GetFrameRate() {
		return frameRate;
	}

	void SetFrameRate(double newFrameRate) {
		frameRate = newFrameRate;
	}

private:

	// Call active modules to perform PreUpdate
	bool PreUpdate();

	// Call active modules to perform Update
	bool Update();

	// Call active modules to perform PostUpdate
	bool PostUpdate();


	//FPS control
	double GetCurrentTime() {
		using namespace std::chrono;
		high_resolution_clock::time_point now = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(now.time_since_epoch());
		return time_span.count();
	}

	void UpdateDeltaTime() {
		double currentTime = GetCurrentTime();
		this->dt = currentTime - this->previousTime;

		this->previousTime = currentTime;
	}
};

extern App* app;