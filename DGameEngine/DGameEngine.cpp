#include "EngineGlobals.h"
#include "DGameEngine.h"
#include "Scene.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "GraphicObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"


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
    gluLookAt( camera.eye.x, camera.eye.y, camera.eye.z,
        camera.center.x, camera.center.y, camera.center.z,
        camera.up.x, camera.up.y, camera.up.z);
      
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
