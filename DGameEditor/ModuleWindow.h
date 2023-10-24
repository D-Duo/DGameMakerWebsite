#pragma once

#include "Module.h"

// Window Configuration -----------
#define WIN_WIDTH (720*4/3)
#define WIN_HEIGHT 720

#define WIN_FULLSCREEN 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define WIN_FULLSCREEN_DESKTOP 0
#define OPENGL 1

class ModuleWindow : public Module
{
public:
	ModuleWindow(bool startEnabled);
	~ModuleWindow();

	void Awake();
	void CleanUp();

	SDL_Window* GetWindow() { return window; }
	SDL_GLContext GetContext() { return gl_context; }

private:
	static SDL_Window* SDLWindowInit();

	static SDL_GLContext CreateWindowContext(SDL_Window* window);
	static void OpenGLInit();

private:
	SDL_Window* window;
	SDL_GLContext gl_context;
};