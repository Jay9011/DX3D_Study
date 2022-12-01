#include "Framework.h"
#include "Target.h"

Target::Target()
{
    collider = new SphereCollider();
    collider->SetParent(this);

    isActive = false;

    hpBar = new Quad(100.0f, 100.0f);
    hpBar->GetMaterial()->SetDiffuseMap(L"Textures/UI/cursor.png");
}

Target::~Target()
{
    delete collider;
    delete hpBar;
}

void Target::Update()
{
    if (!Active())
        return;

    hpBar->position = CAM->WorldToScreenPoint(position + Vector3(0.f, 2.f, 0.f));
    hpBar->UpdateWorld();

    UpdateWorld();
    collider->UpdateWorld();
}

void Target::Render()
{
    if (!Active())
        return;

    Cube::Render();
    collider->Render();
}

void Target::PostRender()
{
    if (!Active())
        return;

    hpBar->Render();
}
