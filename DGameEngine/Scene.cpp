#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::init() {
	CreateGameObject("BakerHouse.fbx", "Baker_house.png");
}

void Scene::postUpdate() {
	for (auto gObj : mGameObjects)
	{
		gObj->UpdateGameObj();
	}
}

void Scene::CreateGameObject(const string meshPath, const string texturePath, mat4 transform) {

	shared_ptr<GameObject> newGameObj = make_shared<GameObject>(meshPath, texturePath, transform);

	AddGameObj(newGameObj);
}

void Scene::AddGameObj(shared_ptr<GameObject> gameObj) {

	mGameObjects.push_back(gameObj);
}