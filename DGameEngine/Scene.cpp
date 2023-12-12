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
		gObj.UpdateGameObj();
	}

}

void Scene::EmptyGameObj() {

    GameObject gameObj;

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
        GameObject object;

        auto meshComp = make_shared<ComponentMesh>(object, mesh);
        auto textComp = make_shared<ComponentMaterial>(object, textures_vec[mesh->mMaterialIndex]);

        object.MeshAddComponent(meshComp);
        object.MaterialAddComponent(textComp);

        mesh->texture = object.GetComponent<ComponentMaterial>()->texture;

        std::string meshName = path;
        mesh.get()->name = meshName;
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

        object.name = meshName;
        myScene.get()->gameObjects.push_back(object);
        i++;
    }
}

int Scene::NameAvailability(std::string name) {
    int count = 0;

    for (const auto& vector : gameObjects) {
        if (vector.name.find(name) != std::string::npos) {
            count++;
        }
    }

    return count;
}