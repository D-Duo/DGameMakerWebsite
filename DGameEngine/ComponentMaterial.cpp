#include "ComponentMaterial.h"

ComponentMaterial::ComponentMaterial(const string path) : Components(type) {

    stringstream ss;
    ss << "../DGameEditor/Assets/Textures/" << path;
    ifstream file(ss.str());
    if (file.good()) {
        auto texture = make_shared<Texture2D>(path);
        mTextures.push_back(texture);
    }
    else {
        cout << "FILE NOT FOUND :: MATERIAL COMPONENT CONSTRUCTOR" << endl;
    }
}

void ComponentMaterial::Enable() {
    SetActive();
}

void ComponentMaterial::Disable() {
    SetDisable();
}

void ComponentMaterial::update() {
    
}