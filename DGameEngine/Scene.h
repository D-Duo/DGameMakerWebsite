#pragma once
#include "EngineGlobals.h"
#include "GameObject.h"
#include "Components.h"
#include "Mesh.h"

class GameObject;

class Scene
{
public:
	Scene(string name);
	~Scene();
	
	void init();
	void GameObjectsUpdate();

	void CreateGameObject(const string meshPath, const string texturePath, mat4 transform = glm::identity<mat4>());

	vector<shared_ptr<GameObject>> gameObjects;

	string name;

	void AddGameObj(shared_ptr<GameObject> gameObj);
	//void RemoveGameObj(shared_ptr<GameObject>);
};

