#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(shared_ptr<Texture2D>&& t) : Components(type) {

    texture = move(t);
}

void ComponentMaterial::Enable() {
    SetActive();
}

void ComponentMaterial::Disable() {
    SetDisable();
}

void ComponentMaterial::update() {
    
}