#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
    terrain = new Terrain();
    terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    player = new Player();
    player->SetTerrain(terrain);

    //ShowCursor(false);

    BulletManager::Get()->CreateBullet();
    TargetManager::Get()->CreateTargets();
    TargetManager::Get()->SetTerrain(terrain);

    Font::Get()->AddColor("White", Float3(1, 1, 1));
    Font::Get()->AddStyle("Default", L"¸¼Àº°íµñ", 30.0f);
    Font::Get()->AddStyle("Big", L"¸¼Àº°íµñ", 50.0f);
    Font::Get()->SetColor("White");
    Font::Get()->SetStyle("Default");

    gameSet.resize(2);
    for (Quad*& img : gameSet)
    {
        img = new Quad(WIN_WIDTH, WIN_HEIGHT);
        img->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
        img->UpdateWorld();
    }
    gameSet[GAMEOVER]->GetMaterial()->SetDiffuseMap(L"Textures/UI/GameOver.png");
    gameSet[CLEAR]->GetMaterial()->SetDiffuseMap(L"Textures/UI/Clear.png");
}

ShootingScene::~ShootingScene()
{
    delete terrain;
    delete player;

    BulletManager::Delete();
    TargetManager::Delete();
    Font::Delete();
}

void ShootingScene::Update()
{
    if (isRunning)
    {
        player->Update();

        BulletManager::Get()->Update();
        TargetManager::Get()->Update();

        if ((int)player->GetHP() <= 0)
        {
            isRunning = false;
            endType = GAMEOVER;
        }
        else if (player->GetScore() >= 10)
        {
            isRunning = false;
            endType = CLEAR;
        }

        if (!isRunning)  // °ÔÀÓÀÌ Á¾·áµÇ¾ú´Ù°í ÆÇ´ÜµÇ¸é
        {
            Font::Get()->SetStyle("Big");
            textYPos = WIN_HEIGHT * 0.4f;
        }
    }
}

void ShootingScene::Render()
{
    player->Render();
    BulletManager::Get()->Render();
    TargetManager::Get()->Render();

    terrain->Render();
}

void ShootingScene::PostRender()
{
    Font::Get()->GetDC()->BeginDraw();

    if (isRunning)
    {
        player->PostRender();
        TargetManager::Get()->PostRender();
    }
    else
    {
        gameSet[endType]->Render();
    }
    Font::Get()->RenderText("Score : " + to_string((int)player->GetScore()), Float2(textXPos, textYPos));

    Font::Get()->GetDC()->EndDraw();
}

void ShootingScene::GUIRender()
{
}

void ShootingScene::PrintTEXT()
{
    
}
