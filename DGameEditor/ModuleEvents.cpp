#include "EditorGlobals.h"
#include "ModuleEvents.h"

ModuleEvents::ModuleEvents()
{
}

ModuleEvents::~ModuleEvents()
{
}

bool ModuleEvents::SDLEventsProcess() {
    SDL_Event event;
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
        }
    }
    return true;
}