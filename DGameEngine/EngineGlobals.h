#pragma once

//INCLIUDES

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
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <glm/ext/matrix_transform.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

//TYPES
typedef glm::dvec3 vec3;
typedef glm::dvec4 vec4;
typedef glm::dmat4 mat4;

//GLOBAL VAR


#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "assimp.lib")

using namespace std;