#pragma once
#include "EngineGlobals.h"
#include "GameObject.h"
#include "Components.h"
#include "Mesh.h"

class GameObject;

class Scene
{
public:
	Scene();
	~Scene();
	
	void init();
	void postUpdate();

	void CreateGameObject(const string meshPath, const string texturePath, mat4 transform = glm::identity<mat4>());

	vector<shared_ptr<GameObject>> mGameObjects;

	void AddGameObj(shared_ptr<GameObject> gameObj);
	//void RemoveGameObj(shared_ptr<GameObject>);
};

