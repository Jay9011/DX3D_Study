#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{
    //cube1 = new Cube();
    //cube1->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Box.png");

    //cube2 = new Cube();
    //cube2->SetParent(cube1);
    //cube2->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt.png");
    //cube2->position.x = 3.0f;

    robot = new Robot();
}

CubeScene::~CubeScene()
{
    //delete cube1;
    //delete cube2;
    delete robot;
}

void CubeScene::Update()
{
    //cube1->rotation.y += 0.0005f;

    //cube1->UpdateWorld();
    //cube2->UpdateWorld();

    robot->Update();
}

void CubeScene::Render()
{
    //cube1->Render();
    //cube2->Render();

    robot->Render();
}

void CubeScene::GUIRender()
{
}
