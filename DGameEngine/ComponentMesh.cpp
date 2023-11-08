#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(shared_ptr<Mesh>&& m) : Components(type) {
    mesh = move(m);

    mMeshes = mesh->loadFromFile("Assets/Meshes/" + mesh->path);
}

void ComponentMesh::Enable() {
    SetActive();
}

void ComponentMesh::Disable() {
    SetDisable();
}

void ComponentMesh::update() {
    mesh->draw();

   for (auto meshes : mMeshes)
   {
        meshes->draw();
   }
}