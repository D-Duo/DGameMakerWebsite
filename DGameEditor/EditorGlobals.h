#pragma once

//INCLIUDES

//    Static Librarys
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <list>
#include <Windows.h>

//    External Librarys
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#pragma comment(lib, "shell32.lib")

using namespace std;



// GLOBAL ENUM
enum States
{
	DISABLED,
	ENABLED,
};

// DEFINES
#define TITLE "D. Game Maker"

// Deletes a buffer
#define RELEASE( x ) \
	{						\
	if( x != NULL )		\
		{					  \
	  delete x;			\
	  x = NULL;			  \
		}					  \
	}

struct I_Point {
	int x, y;
};