#include "EditorGlobals.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

ModuleWindow::~ModuleWindow()
{
}

SDL_Window* ModuleWindow::SDLWindowInit() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw exception(SDL_GetError());

    SDL_version compiled;
    SDL_VERSION(&compiled);
    cout << "SDL Compiled with " << to_string(compiled.major) << '.' << to_string(compiled.minor) << '.' << to_string(compiled.patch) << endl;

    SDL_version linked;
    SDL_GetVersion(&linked);
    cout << "SDL Linked with " << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch) << endl;

    // setup SDL window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // GL 3.1 + GLSL 130
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    Uint32 flags = SDL_WINDOW_SHOWN;
    if (WIN_FULLSCREEN == true) flags |= SDL_WINDOW_FULLSCREEN;
    if (WIN_BORDERLESS == true) flags |= SDL_WINDOW_BORDERLESS;
    if (WIN_RESIZABLE == true) flags |= SDL_WINDOW_RESIZABLE;
    if (WIN_FULLSCREEN_DESKTOP == true) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    if (OPENGL == true) flags |= SDL_WINDOW_OPENGL;

    auto window = SDL_CreateWindow("SDL+OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, flags);
    if (!window) throw exception(SDL_GetError());

    return window;
}

void ModuleWindow::SDLWindowCleanUp() {

}