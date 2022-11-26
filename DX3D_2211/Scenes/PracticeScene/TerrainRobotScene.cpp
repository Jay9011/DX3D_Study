#include "Framework.h"
#include "TerrainRobotScene.h"

TerrainRobotScene::TerrainRobotScene()
{
    //terrain = new Terrain();
    //terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    robot = new Robot();
}

TerrainRobotScene::~TerrainRobotScene()
{
    delete robot;
    //delete terrain;
}

void TerrainRobotScene::Update()
{
    robot->Update();
}

void TerrainRobotScene::Render()
{
    robot->Render();
    //terrain->Render();
}

void TerrainRobotScene::GUIRender()
{
}
