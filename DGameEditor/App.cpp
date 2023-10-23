#include "App.h"

App::App(int argc, char* args[]) : argc(argc), args(args) {
    
    // Create the modules here (module = new Module(true);)

    // Add the modules to the modules list in the proper order (AddModule(module);)

}

App::~App()
{
    // Release modules
    this->modules.clear();
}

void App::AddModule(Module* module) {
    this->modules.push_back(module);
}

void App::Awake() {
    targetFrameTime = 1 / frameRate;

    for (const auto& item : modules)
    {
        item->Awake();
        cout << "Performed Awake of Module " << item->name << endl;
    }
}

void App::Start() {

    for (const auto& item : modules)
    {
        if (item->GetState() == States::DISABLED)
            continue;

        item->Start();
        cout << "Performed Start of Module " << item->name << endl;
    }
}

bool App::DoUpdate() {
	// Record the start time of the frame
	auto frameStartTime = std::chrono::high_resolution_clock::now();

    // Update the delta time for this frame execution
    this->UpdateDeltaTime();

	// Update the active modules
	this->PreUpdate();

	this->Update();

	this->PostUpdate();

    // Calculate the elapsed time for the frame
    auto frameEndTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> frameDuration = frameEndTime - frameStartTime;

    // Calculate the sleep time based on the current target frame rate
    double sleepTime = targetFrameTime - frameDuration.count();

    if (sleepTime > 0) {
        std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
    }
}

bool App::PreUpdate() {

    for (const auto& item : modules)
    {
        if (item->GetState() == States::DISABLED)
            continue;

        item->PreUpdate();
        cout << "Performed PreUpdate of Module " << item->name << endl;
    }
}

bool App::Update() {

    for (const auto& item : modules)
    {
        if (item->GetState() == States::DISABLED)
            continue;

        item->Update();
        cout << "Performed Update of Module " << item->name << endl;
    }
}

bool App::PostUpdate() {

    for (const auto& item : modules)
    {
        if (item->GetState() == States::DISABLED)
            continue;

        item->PostUpdate();
        cout << "Performed PostUpdate of Module " << item->name << endl;
    }
}

void App::CleanUp() {

    for (const auto& item : modules)
    {
        item->CleanUp();
        cout << "Performed CleanUp of Module " << item->name << endl;
    }
}