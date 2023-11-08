#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(shared_ptr<Mesh>&& m) : Components(type) {
    mesh = move(m);
}

void ComponentMesh::Enable() {
    SetActive();
}

void ComponentMesh::Disable() {
    SetDisable();
}

void ComponentMesh::update() {
    mesh->draw();
}