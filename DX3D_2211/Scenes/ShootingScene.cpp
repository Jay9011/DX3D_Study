#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
    terrain = new Terrain();
    terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");

    player = new Player();
    player->SetTerrain(terrain);

    ShowCursor(false);

    BulletManager::Get()->CreateBullet();
}

ShootingScene::~ShootingScene()
{
    delete terrain;
    delete player;

    BulletManager::Delete();
}

void ShootingScene::Update()
{
    player->Update();

    BulletManager::Get()->Update();
}

void ShootingScene::Render()
{
    BulletManager::Get()->Render();

    terrain->Render();
}

void ShootingScene::PostRender()
{
    player->PostRender();
}

void ShootingScene::GUIRender()
{
}
