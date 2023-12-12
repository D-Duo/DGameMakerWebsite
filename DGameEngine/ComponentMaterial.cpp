#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(GameObject& owner, shared_ptr<Texture2D> texture) : Component(owner) {
    this->texture = texture;
}

void ComponentMaterial::update() {
    //owner.GetComponent<ComponentMesh>()->mesh.get()->texture = this->texture;
}