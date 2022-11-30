#include "Framework.h"
#include "FirstPersonShooterScene.h"

FirstPersonShooterScene::FirstPersonShooterScene()
{
    terrain = new Terrain();
    terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Floor.png");
    terrain->GetMaterial()->SetNormalMap(L"Textures/Landscape/Floor_normal.png");

    crosshair = new Quad(100.0f, 100.0f);
    crosshair->GetMaterial()->SetDiffuseMap(L"Textures/UI/cursor.png");
    crosshair->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
    crosshair->UpdateWorld();

    sphereMgr = new SphereManager();
    isActiveSphere = sphereMgr->GetActiveList();

    sphereSpawner = new SphereSpawner();

    terrainWidth = terrain->GetWidth();
    terrainLength = terrain->GetLength();
}

FirstPersonShooterScene::~FirstPersonShooterScene()
{
    delete terrain;
    delete crosshair;
    delete sphereMgr;
    delete sphereSpawner;
}

void FirstPersonShooterScene::Update()
{
    Camera* camera = Environment::Get()->GetMainCamera();
    Vector3 position = camera->position;

    camera->position.y = terrain->GetHeight(position) + VIEW_HEIGHT;

    if (MOUSE_DOWN(0))
    {
        sphereMgr->Shoot(position, camera->Forward());
    }

    SphereSpawn();
    CollideCheck();
    
    sphereMgr->Update();
    sphereSpawner->Update();
}

void FirstPersonShooterScene::Render()
{
    terrain->Render();
    sphereMgr->Render();
    sphereSpawner->Render();
}

void FirstPersonShooterScene::PostRender()
{
    crosshair->Render();
}

void FirstPersonShooterScene::GUIRender()
{
}

void FirstPersonShooterScene::SphereSpawn()
{
    int spawnX = Random(0, terrainWidth);
    int spawnZ = Random(0, terrainLength);
    int spawnY = terrain->GetHeight({ (float)spawnX, 0.0f, (float)spawnZ }) + sphereSpawner->GetRadius();

    static float timer = 0.0f;
    timer += DELTA;
    if (timer >= 5.0f)
    {
        timer = 0;
        sphereSpawner->Spawn({ (float)spawnX, (float)spawnY, (float)spawnZ });
    }
}

void FirstPersonShooterScene::CollideCheck()
{
    for (int i = 0; i < isActiveSphere->size(); i++)
    {
        if (!isActiveSphere->at(i))
            continue;

        if (sphereSpawner->IsCollided(sphereMgr->GetCollider(i)))
        {
            sphereMgr->Inactive(i);
        }
    }
}
