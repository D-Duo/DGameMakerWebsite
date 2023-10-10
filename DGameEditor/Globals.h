#pragma once

#pragma comment(lib, "shell32.lib")

using namespace std;

//GLOBAL VAR


//INCLIUDES
#include "..\DGameEngine\DGameEngine.h"

//    Static Librarys
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

//    External Librarys
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

//    Project Files
//        Headers
#include "ModuleWindow.h"
#include "ModuleGL.h"
#include "ModuleEvents.h"
#include "ModuleGUI.h"