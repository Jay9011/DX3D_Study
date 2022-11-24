#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{
    cube1 = new Cube();
    cube1->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Box.png");

    cube2 = new Cube();
    cube2->SetParent(cube1);
    cube2->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt.png");
    cube2->position.x = 3.0f;
}

CubeScene::~CubeScene()
{
    delete cube1;
    delete cube2;
}

void CubeScene::Update()
{
    cube1->rotation.y += 0.0001f;

    cube1->UpdateWorld();
    cube2->UpdateWorld();
}

void CubeScene::Render()
{
    cube1->Render();
    cube2->Render();
}

void CubeScene::GUIRender()
{
}
