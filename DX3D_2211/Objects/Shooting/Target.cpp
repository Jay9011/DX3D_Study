#include "Framework.h"
#include "Target.h"

Target::Target()
{
    collider = new SphereCollider();
    collider->SetParent(this);

    isActive = false;
}

Target::~Target()
{
    delete collider;
}

void Target::Update()
{
    if (!Active())
        return;

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
