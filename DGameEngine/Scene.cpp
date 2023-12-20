#include "Scene.h"
#include "Mesh.h"
#include "Loaders.h"
#include "ComponentTransform.h"

Scene::Scene(string name) : name(name) {

}

Scene::~Scene() {

}

void Scene::init() {
	
}

void Scene::GameObjectsUpdate() {
	for (auto& gObj : gameObjects)
	{
        gObj->UpdateGameObj();
	}

}

void Scene::EmptyGameObj() {

    unique_ptr<GameObject> gameObj;

	string meshName = "GameObject";
	int currentCopies = NameAvailability(meshName);
	if (currentCopies > 0) {
		meshName.append("(");
		std::string copiesToString = std::to_string(currentCopies);
		meshName.append(copiesToString);
		meshName.append(")");
	}

	gameObjects.push_back(move(gameObj));
}


void Scene::loadFromFile(const string& path, shared_ptr<Scene> myScene) {
    auto meshes_vec = FileLoader::MeshloadFromFile(path);
    auto textures_vec = FileLoader::TextureloadFromFile(path);
    auto transforms_vec = FileLoader::TransformloadFromFile(path, meshes_vec);

    unique_ptr<GameObject> parent_ = make_unique<GameObject>();

    int currentIndex = IndexAvailability();
    parent_->SetIndex(currentIndex);
    parent_->SetActive();

    int i = 0;
    for (const auto& mesh : meshes_vec)
    {
        unique_ptr<GameObject> object = make_unique<GameObject>();

        object->GetComponent<ComponentTransform>()->TransformSetter(transforms_vec[i]);

        unique_ptr<ComponentMesh> meshComp = make_unique<ComponentMesh>(mesh);
        unique_ptr<ComponentMaterial> textComp = make_unique<ComponentMaterial>(textures_vec[mesh->mMaterialIndex]);

        object->MeshAddComponent(move(meshComp));
        object->MaterialAddComponent(move(textComp));

        mesh->texture = object->GetComponent<ComponentMaterial>()->texture;

        std::string meshName = path;
        mesh->name = meshName;
        size_t pos = meshName.find(".FBX");

        while (pos != std::string::npos) {
            meshName.erase(pos, 4);
            pos = meshName.find(".FBX", pos);
        }

        int currentCopies = NameAvailability(meshName);
        if (currentCopies > 0) {
            meshName.append("(");
            std::string copiesToString = std::to_string(currentCopies);
            meshName.append(copiesToString);
            meshName.append(")");
        }

        object->SetName(meshName);

        i++;
        object->SetIndex(currentIndex + i);
        object->SetActive();

        //add child to parent
        parent_->addChild(move(object));

        //myScene->gameObjects.push_back(move(object));
    }

    string parentName = "gameObj";
    int currentCopies = NameAvailability(parentName);
    if (currentCopies > 0) {
        parentName.append("(");
        std::string copiesToString = std::to_string(currentCopies);
        parentName.append(copiesToString);
        parentName.append(")");
    }
    parent_->SetName(parentName);

    //add parent to scene
    myScene->gameObjects.push_back(move(parent_));
}

void Scene::DeleteGameObj(int index_todelete) {
    
    //forward
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i]->GetIndex() == index_todelete)
        {
            gameObjects[i].reset();
            gameObjects.erase(gameObjects.begin() + i);
            break;
        }
        else
        {
            auto& gObj_todelete = gameObjects[i];
            auto& child_todelete = gObj_todelete->GetChildren();
            //int childIndex_end = gObj_todelete->GetChildren().size() + i;

            //if (childIndex_end >= index_todelete)
            //{
                for (int c = 0; c < gObj_todelete->GetChildren().size(); c++)
                {
                    if (child_todelete[c]->GetIndex() == index_todelete)
                    {
                        child_todelete[c].reset();
                        child_todelete.erase(child_todelete.begin() + c);
                        break;
                    }
                }
            //}
        }
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

int Scene::IndexAvailability() {
    int count = 0;

    for (auto& gObj : gameObjects)
    {
        if (gObj->GetIndex() == count) { count++; }
    }
    return count;
}