#include "EditorGlobals.h"
#include "App.h"
#include "ModuleEvents.h"

ModuleEvents::ModuleEvents(bool startEnabled) : Module(startEnabled)
{
    name = "events";

    keyboard = new KEY_STATE[MAX_KEYS];
    memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
}

ModuleEvents::~ModuleEvents() { delete[] keyboard; }

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

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    for (int i = 0; i < MAX_KEYS; ++i)
    {
        if (keys[i] == 1)
        {
            if (keyboard[i] == KEY_IDLE)
                keyboard[i] = KEY_DOWN;
            else
                keyboard[i] = KEY_REPEAT;
        }
        else
        {
            if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
                keyboard[i] = KEY_UP;
            else
                keyboard[i] = KEY_IDLE;
        }
    }

    Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
    mouse_z = 0;

    for (int i = 0; i < 5; ++i)
    {
        if (buttons & SDL_BUTTON(i))
        {
            if (mouse_buttons[i] == KEY_IDLE)
                mouse_buttons[i] = KEY_DOWN;
            else
                mouse_buttons[i] = KEY_REPEAT;
        }
        else
        {
            if (mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
                mouse_buttons[i] = KEY_UP;
            else
                mouse_buttons[i] = KEY_IDLE;
        }
    }

    mouse_motion_x = mouse_motion_y = 0;

    string filePath;
    string mPath;
    string tPath;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type) {
        case SDL_MOUSEWHEEL:
            mouse_z = event.wheel.y;
            break;

        case SDL_MOUSEMOTION:
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;

            mouse_motion_x = event.motion.xrel;
            mouse_motion_y = event.motion.yrel;
            break;

        case SDL_QUIT: return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            }
            break;
        case SDL_DROPFILE:

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
            //app->engineManager->sel_Scene.scene.get()->CreateGameObject(mPath, tPath);

            SDL_free(event.drop.file);  // Free files memory

            break;
        case SDL_WINDOWEVENT:

            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                auto newWidth = app->window->GetWindowSize().x;
                auto newHeight = app->window->GetWindowSize().y;
                glViewport(0, 0, newWidth, newHeight);
                /*float aspectRatio = (float)newWidth / (float)newHeight;
                glm::mat4 projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);*/
            }

            break;
        }
    }

    return true;
}