#include "Scene.h"
#include "Mesh.h"
#include "Loaders.h"

Scene::Scene(string name) : name(name) {

}

Scene::~Scene() {

}

void Scene::init() {
	
}

void Scene::GameObjectsUpdate() {
	for (auto gObj : gameObjects)
	{
        gObj->UpdateGameObj();
	}

}

void Scene::EmptyGameObj() {

    shared_ptr<GameObject> gameObj;

	string meshName = "GameObject";
	int currentCopies = NameAvailability(meshName);
	if (currentCopies > 0) {
		meshName.append("(");
		std::string copiesToString = std::to_string(currentCopies);
		meshName.append(copiesToString);
		meshName.append(")");
	}

	gameObjects.push_back(gameObj);
}

void Scene::loadFromFile(const string& path, shared_ptr<Scene> myScene) {
    auto meshes_vec = FileLoader::MeshloadFromFile(path);
    auto textures_vec = FileLoader::TextureloadFromFile(path);

    int i = 0;
    for (const auto& mesh : meshes_vec)
    {
        shared_ptr<GameObject> object = make_shared<GameObject>();

        unique_ptr<ComponentMesh> meshComp = make_unique<ComponentMesh>(mesh);
        unique_ptr<ComponentMaterial> textComp = make_unique<ComponentMaterial>(textures_vec[mesh->mMaterialIndex]);

        object->MeshAddComponent(move(meshComp));
        object->MaterialAddComponent(move(textComp));

        mesh->texture = object->GetComponent<ComponentMaterial>()->texture;

        std::string meshName = path;
        mesh->name = meshName;
        size_t pos = meshName.find(".fbx");

        while (pos != std::string::npos) {
            meshName.erase(pos, 4);
            pos = meshName.find(".fbx", pos);
        }
        int currentCopies = NameAvailability(meshName);
        if (currentCopies > 0) {
            meshName.append("(");
            std::string copiesToString = std::to_string(currentCopies);
            meshName.append(copiesToString);
            meshName.append(")");
        }

        object->GetName() = meshName;
        myScene->gameObjects.push_back(object);
        i++;
    }
}

int Scene::NameAvailability(std::string name) {
    int count = 0;

    for (const auto& vector : gameObjects) {
        if (vector->GetName().find(name) != std::string::npos) {
            count++;
        }
    }

    return count;
}