#pragma once

// Window Configuration -----------
#define WIN_WIDTH (576*4/3)
#define WIN_HEIGHT 576

#define WIN_FULLSCREEN 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define WIN_FULLSCREEN_DESKTOP 0
#define OPENGL 1

class ModuleWindow
{
public:
	ModuleWindow();
	~ModuleWindow();

	static SDL_Window* SDLWindowInit();
	static void SDLWindowCleanUp();

private:

};