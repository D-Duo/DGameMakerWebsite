#include "EditorGlobals.h"
#include "App.h"
#include "ModuleEvents.h"

ModuleEvents::ModuleEvents(bool startEnabled) : Module(startEnabled)
{
    name = "events";
}

ModuleEvents::~ModuleEvents() {}

void ModuleEvents::Awake() {
    SDL_Init(0);

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) throw exception(SDL_GetError());
}

bool ModuleEvents::PreUpdate() {
    bool ret;

    ret = this->SDLEventsProcess();

    return ret;
}

bool ModuleEvents::SDLEventsProcess() {
    SDL_PumpEvents();

    static SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type) {
        case SDL_QUIT: return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            }
            break;
        case SDL_DROPFILE:
            string filePath;
            string mPath;
            string tPath;
            filePath = event.drop.file;

            if (filePath.substr(filePath.find_last_of(".") + 1) == "fbx") {
                cout << ".fbx file detected" << endl;
                mPath = filePath;
                size_t lastBackslashPos = mPath.find_last_of('\\');
                if (lastBackslashPos != string::npos) {
                    mPath.erase(0, lastBackslashPos + 1);
                }

            }
            if (filePath.substr(filePath.find_last_of(".") + 1) == "png") {
                cout << ".png file detected" << endl;
                tPath = filePath;
                size_t lastBackslashPos = tPath.find_last_of('\\');
                if (lastBackslashPos != string::npos) {
                    tPath.erase(0, lastBackslashPos + 1);
                }
            }
            
            app->engineManager->GetEngine()->meshLoader.loadFromFile(mPath, app->engineManager->GetEngine()->myScene);

            SDL_free(event.drop.file);  // Free files memory

            break;
        }
    }

    return true;
}