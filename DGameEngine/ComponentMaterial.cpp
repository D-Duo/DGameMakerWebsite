#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(shared_ptr<Texture2D> texture) {
    this->texture = texture;
}

void ComponentMaterial::update() {
    //change texture if called
    //owner->GetComponent<ComponentMesh>()->mesh->texture = this->texture;
    //owner.GetComponent<ComponentMesh>()->mesh->texture = this->texture;
}