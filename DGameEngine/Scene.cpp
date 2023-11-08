#include "Scene.h"
#include "Mesh.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::init() {
	//CreateGameObject("BakerHouse.fbx", "Baker_house.png");
}

void Scene::postUpdate() {
	for (auto gObj : mGameObjects)
	{
		gObj->UpdateGameObj();
	}

}

void Scene::CreateGameObject(const string meshPath, const string texturePath, mat4 transform) {

	//shared_ptr<GameObject> newGameObj = make_shared<GameObject>(meshPath, texturePath, transform);

	//newGameObj->isActive = true;

	////eliminate .fbx for naming the gObj
	//string _name = meshPath;
	//size_t dotPos = _name.rfind('.');
	//if (dotPos != string::npos && dotPos != 0) {
	//	newGameObj->textPath = _name.substr(0, dotPos);
	//}
	//else {
	//	newGameObj->textPath = _name;//no extension found
	//}

	//AddGameObj(newGameObj);

	//stringstream ss;
	//ss << "../DGameEditor/Assets/Meshes/" << meshPath;
	//ifstream file(ss.str());
	//if (file.good()) {
	//	mMeshes = Mesh::loadFromFile(ss.str());
	//}
	//else {
	//	cout << "FILE NOT FOUND :: MESH COMPONENT CONSTRUCTOR" << endl;
	//}
}

void Scene::CreateGameObject(const string path, shared_ptr<Mesh>&& mesh, shared_ptr<Texture2D>&& texture) {

	shared_ptr<GameObject> newGameObj = make_shared<GameObject>();
	shared_ptr<Components> newComp = nullptr;

	//create name for gObj
	string _name = path;

	size_t dotPos = _name.rfind('.');
	if (dotPos != string::npos && dotPos != 0) {
		_name.substr(4, dotPos);
	}

	size_t lastBackslashPos = _name.find_last_of('\\');
	if (lastBackslashPos != string::npos) {
		_name.erase(0, lastBackslashPos + 1);
	}

	newGameObj->SetTag(numGobj);
	newGameObj->SetName(_name + "_" + to_string(newGameObj->GetTag()).c_str());
	newGameObj->SetActive();
	numGobj++;

	newComp = newGameObj->CreateComponent(COMPONENT_MESTH, move(mesh), move(texture));
	newGameObj->AddComponent(newComp);
	newComp = newGameObj->CreateComponent(COMPONENT_MATERIAL, move(mesh), move(texture));
	newGameObj->AddComponent(newComp);

	AddGameObj(newGameObj);
}

void Scene::AddGameObj(shared_ptr<GameObject> gameObj) {

	mGameObjects.push_back(gameObj);
}