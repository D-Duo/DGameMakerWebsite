#pragma once

//INCLUDES

//    Static Librarys
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>
#include <memory>
#include <string>
#include <span>
#include <array>
#include <filesystem>
#include <fstream>
#include <regex>

//    External Librarys
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <IL/il.h>

#include <glm/ext/matrix_transform.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <chrono>

//TYPES
typedef glm::dvec3 vec3;
typedef glm::dvec4 vec4;
typedef glm::dmat4 mat4;

using vec2f = glm::vec2;
using vec3f = glm::vec3;
using vec4f = glm::vec4;

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "assimp-vc143-mt.lib")
#pragma comment(lib, "DevIL.lib")

using namespace std;
using namespace chrono;

//GLOBAL VAR
static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;
