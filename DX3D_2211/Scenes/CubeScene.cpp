#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{
    cube1 = new Cube();
    cube1->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Box.png");

    cube2 = new Cube();
    cube2->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Box.png");
    cube2->SetPos({ 3.0f, 0.0f, 0.0f });
}

CubeScene::~CubeScene()
{
    delete cube1;
    delete cube2;
}

void CubeScene::Update()
{
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
