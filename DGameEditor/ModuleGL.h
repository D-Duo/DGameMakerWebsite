#pragma once

class ModuleGL
{
public:
	ModuleGL();
	~ModuleGL();

	static SDL_GLContext CreateWindowContext(SDL_Window* window);
	static void OpenGLInit();

	static void GLCleanUp();

private:

};