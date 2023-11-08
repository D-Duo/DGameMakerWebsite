#pragma once
#include "Scene.h"
#include "Graphic.h"
#include "Texture2D.h"
#include "Components.h"
#include "Mesh.h"

class MeshLoader{
public:

	void loadFromFile(const string& path, Scene& myScene);
};