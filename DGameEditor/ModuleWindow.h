#pragma once

#include "Module.h"

// Window Configuration -----------
#define WIN_WIDTH (720*16/9)
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
	bool PreUpdate();
	void CleanUp();

	SDL_Window* GetWindow() { return window; }
	SDL_GLContext GetContext() { return gl_context; }
	void UpdateWindowContext(SDL_Window* window, SDL_GLContext gl_context);

	I_Point GetWindowSize() {
		return windowSize;
	}

private:
	static SDL_Window* SDLWindowInit();

	static SDL_GLContext CreateWindowContext(SDL_Window* window);
	static void OpenGLInit();

private:
	I_Point windowSize; // x = width  ||  y = height
	SDL_Window* window;
	SDL_GLContext gl_context;
};