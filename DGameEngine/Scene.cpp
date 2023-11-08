#include "Scene.h"
#include "Mesh.h"

Scene::Scene(string name) : name(name) {

}

Scene::~Scene() {

}

void Scene::init() {
	CreateGameObject("BakerHouse.fbx", "Baker_house.png");
}

void Scene::GameObjectsUpdate() {
	for (auto gObj : gameObjects)
	{
		gObj->UpdateGameObj();
	}

}

void Scene::CreateGameObject(const string meshPath, const string texturePath, mat4 transform) {

	shared_ptr<GameObject> newGameObj = make_shared<GameObject>(meshPath, texturePath, transform);

	newGameObj->isActive = true;

	//eliminate .fbx for naming the gObj
	string _name = meshPath;
	size_t dotPos = _name.rfind('.');
	if (dotPos != string::npos && dotPos != 0) {
		newGameObj->textPath = _name.substr(0, dotPos);
	}
	else {
		newGameObj->textPath = _name;//no extension found
	}

	AddGameObj(newGameObj);
}

void Scene::AddGameObj(shared_ptr<GameObject> gameObj) {

	gameObjects.push_back(gameObj);
}