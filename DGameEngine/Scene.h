#pragma once
#include "EngineGlobals.h"
#include "GameObject.h"
#include "Components.h"
#include "Mesh.h"
#include "Texture2D.h"

class GameObject;
class Mesh;
class Texture2D;

class Scene
{
public:
	Scene(string name);
	~Scene();
	
	void init();
	void GameObjectsUpdate();

	vector<GameObject> gameObjects;
	string name;

	void loadFromFile(const string& path, shared_ptr<Scene> myScene);
	void EmptyGameObj();
	//void RemoveGameObj(shared_ptr<GameObject>);

	int NameAvailability(std::string name);
};

