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
    TargetManager::Get()->CreateTargets();
    TargetManager::Get()->SetTerrain(terrain);
}

ShootingScene::~ShootingScene()
{
    delete terrain;
    delete player;

    BulletManager::Delete();
    TargetManager::Delete();
}

void ShootingScene::Update()
{
    player->Update();

    BulletManager::Get()->Update();
    TargetManager::Get()->Update();
}

void ShootingScene::Render()
{
    BulletManager::Get()->Render();
    TargetManager::Get()->Render();

    terrain->Render();
}

void ShootingScene::PostRender()
{
    player->PostRender();
    TargetManager::Get()->PostRender();
}

void ShootingScene::GUIRender()
{
}
