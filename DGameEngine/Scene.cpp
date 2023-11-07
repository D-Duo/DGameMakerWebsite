#include "Scene.h"
#include "Mesh.h"

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

	mGameObjects.push_back(gameObj);
}