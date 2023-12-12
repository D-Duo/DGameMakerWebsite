#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(GameObject& owner, shared_ptr<Mesh> mesh) : Component(owner) {
    this->mesh = mesh;
}

void ComponentMesh::update() {
    mesh.get()->draw();
}