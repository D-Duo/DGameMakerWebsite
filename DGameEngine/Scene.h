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
	Scene();
	~Scene();
	
	void init();
	void postUpdate();

	void CreateGameObject(const string meshPath, const string texturePath, mat4 transform = glm::identity<mat4>());

	void CreateGameObject(const string path, shared_ptr<Mesh>&& mesh, shared_ptr<Texture2D>&& t);

	vector<shared_ptr<GameObject>> mGameObjects;
	shared_ptr<GameObject> selectedGobj;

	int numGobj = 0;

	void AddGameObj(shared_ptr<GameObject> gameObj);
	void RemoveGameObj(shared_ptr<GameObject> gObj);
};

