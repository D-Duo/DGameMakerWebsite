#include "EngineGlobals.h"
#include "DGameEngine.h"
#include "Scene.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "GraphicObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"

GameEngine::GameEngine() {
    ilInit();
    const string mp = "Baker_house.fbx";
}

GameEngine::~GameEngine(){}

void GameEngine::render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(engineCamera.get()->GetComponent<ComponentCamera>()->fov, engineCamera.get()->GetComponent<ComponentCamera>()->aspect, engineCamera.get()->GetComponent<ComponentCamera>()->zNear, engineCamera.get()->GetComponent<ComponentCamera>()->zFar);

    engineCamera.get()->GetComponent<ComponentCamera>()->lookAtPos = engineCamera.get()->GetComponent<ComponentTransform>()->GetPosition() + engineCamera.get()->GetComponent<ComponentTransform>()->GetForward() * engineCamera.get()->GetComponent<ComponentCamera>()->camOffset;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //Update camera look at position

    gluLookAt(engineCamera.get()->GetComponent<ComponentTransform>()->GetPosition().x, engineCamera.get()->GetComponent<ComponentTransform>()->GetPosition().y, engineCamera.get()->GetComponent<ComponentTransform>()->GetPosition().z,
        engineCamera.get()->GetComponent<ComponentCamera>()->lookAtPos.x, engineCamera.get()->GetComponent<ComponentCamera>()->lookAtPos.y, engineCamera.get()->GetComponent<ComponentCamera>()->lookAtPos.z,
        engineCamera.get()->GetComponent<ComponentTransform>()->GetUp().x, engineCamera.get()->GetComponent<ComponentTransform>()->GetUp().y, engineCamera.get()->GetComponent<ComponentTransform>()->GetUp().z);
        
#pragma region Draw Sandbox
    /*static auto mesh_ptrs = Mesh::loadFromFile("Assets/Meshes/BakerHouse.fbx");
  
    GraphicObject mesh1(mesh_ptrs.front());
    GraphicObject mesh2(mesh_ptrs.back());
  
    GraphicObject house;
  
    house.addChild( std::move(mesh1));
    house.addChild( std::move(mesh2));
  
    GraphicObject root;
    root.addChild(std::move(house));
  
    root.paint();*/
  
#pragma endregion
  
#pragma region direct draw test

  
#pragma endregion

}
