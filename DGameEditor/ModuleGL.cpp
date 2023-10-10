#include "EditorGlobals.h"
#include "ModuleGL.h"
#include "ModuleWindow.h"

ModuleGL::ModuleGL()
{
}

ModuleGL::~ModuleGL()
{
}

SDL_GLContext ModuleGL::CreateWindowContext(SDL_Window* window) {
    auto gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) throw exception(SDL_GetError());
    if (SDL_GL_MakeCurrent(window, gl_context) != 0) throw exception(SDL_GetError());
    if (SDL_GL_SetSwapInterval(1) != 0) throw exception(SDL_GetError());
    return gl_context;
}

void ModuleGL::OpenGLInit() {
    auto glew_init_error = glewInit();
    if (glew_init_error != GLEW_OK) throw exception((char*)glewGetErrorString(glew_init_error));
    if (!GLEW_VERSION_3_1) throw exception("OpenGL 3.1 Not Supported!");
    glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}