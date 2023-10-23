#pragma once

//INCLIUDES
#include "..\DGameEngine\DGameEngine.h"

//    Static Librarys
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <list>

//    External Librarys
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#pragma comment(lib, "shell32.lib")

using namespace std;



// GLOBAL ENUM
enum class Update_Status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
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