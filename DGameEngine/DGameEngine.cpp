#include "EngineGlobals.h"
#include "DGameEngine.h"
#include "Scene.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "GraphicObject.h"

GameEngine::GameEngine() {
    ilInit();
    const string mp = "Baker_house.fbx";
}

GameEngine::~GameEngine(){}

void GameEngine::render() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(mainCamera.fov, mainCamera.aspect, mainCamera.clippingPlaneNear, mainCamera.clippingPlaneFar);
  
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Update camera look at position

    gluLookAt( mainCamera.position.x, mainCamera.position.y, mainCamera.position.z,
        mainCamera.orientation.x, mainCamera.orientation.y, mainCamera.orientation.z,
        mainCamera.up.x, mainCamera.up.y, mainCamera.up.z);  
        
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
