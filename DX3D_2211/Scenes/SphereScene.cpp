#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
    sphere = new Sphere(10.0f);
    sphere->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");
    sphere->GetMaterial()->SetSpecularMap(L"Textures/Landscape/Fieldstone_SM.tga");
}

SphereScene::~SphereScene()
{
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

void SphereScene::GUIRender()
{
    sphere->GetMaterial()->GUIRender();
}
