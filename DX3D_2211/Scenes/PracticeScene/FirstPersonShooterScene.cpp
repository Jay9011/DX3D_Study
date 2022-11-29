#include "Framework.h"
#include "FirstPersonShooterScene.h"

FirstPersonShooterScene::FirstPersonShooterScene()
{
    terrain = new Terrain();
    terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    sphereMgr = new SphereManager();

    crosshair = new Quad(100.0f, 100.0f);
    crosshair->GetMaterial()->SetDiffuseMap(L"Textures/UI/crosshair.png");
    crosshair->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
}

FirstPersonShooterScene::~FirstPersonShooterScene()
{
    delete terrain;
    delete sphereMgr;
    delete crosshair;
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

    sphereMgr->Update();

    crosshair->UpdateWorld();
}

void FirstPersonShooterScene::Render()
{
    terrain->Render();
    sphereMgr->Render();
}

void FirstPersonShooterScene::PostRender()
{
    crosshair->Render();
}

void FirstPersonShooterScene::GUIRender()
{
}

void FirstPersonShooterScene::FirstPersonView()
{
    
}