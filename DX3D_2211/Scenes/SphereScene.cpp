#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
    sphere = new Sphere(10.0f);
    sphere->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");
    sphere->GetMaterial()->SetSpecularMap(L"Textures/Landscape/Fieldstone_SM.tga");
    sphere->GetMaterial()->SetNormalMap(L"Textures/Landscape/Fieldstone_NM.tga");

    quad = new Quad(50.0f, 50.0f);
    quad->GetMaterial()->SetDiffuseMap(L"Textures/UI/cursor.png");
    quad->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
    quad->UpdateWorld();
}

SphereScene::~SphereScene()
{
    delete quad;
    delete sphere;
}

void SphereScene::Update()
{
    sphere->rotation.y += DELTA;

    sphere->UpdateWorld();
}

void SphereScene::Render()
{
    sphere->Render();
}

void SphereScene::PostRender()
{
    quad->Render();
}

void SphereScene::GUIRender()
{
    sphere->GetMaterial()->GUIRender();
}
