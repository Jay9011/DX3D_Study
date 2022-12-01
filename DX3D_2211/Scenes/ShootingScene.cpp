#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
    terrain = new Terrain();
    terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");

    player = new Player();
    player->SetTerrain(terrain);

    ShowCursor(false);
}

ShootingScene::~ShootingScene()
{
    delete terrain;
    delete player;
}

void ShootingScene::Update()
{
    player->Update();
}

void ShootingScene::Render()
{
    terrain->Render();
}

void ShootingScene::PostRender()
{
    player->PostRender();
}

void ShootingScene::GUIRender()
{
}
