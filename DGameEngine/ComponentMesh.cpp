#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(const string path) : Components(type) {

    stringstream ss;
    ss << "../DGameEditor/Assets/Meshes/" << path;
    ifstream file(ss.str());
    if (file.good()) {
        mMeshes = Mesh::loadFromFile(ss.str());
    }
    else {
        cout << "FILE NOT FOUND :: MESH COMPONENT CONSTRUCTOR" << endl;
    }
}

void ComponentMesh::Enable() {
    SetActive();
}

void ComponentMesh::Disable() {
    SetDisable();
}

void ComponentMesh::update() {
    for (auto meshes : mMeshes)
    {
        meshes->draw();
    }
}