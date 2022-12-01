#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
    terrain = new Terrain();
    player = new Player();
    player->SetTerrain(terrain);
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
