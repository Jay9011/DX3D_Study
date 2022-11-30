#include "Framework.h"

SphereSpawner::SphereSpawner(float radius, UINT poolCount) :
    COUNT(poolCount),
    radius(radius)
{
    spheres.resize(COUNT);
    isActive.resize(COUNT);
    colliders.resize(COUNT);
    for (int i = 0; i < COUNT; i++)
    {
        spheres[i] = new Sphere(this->radius);
        spheres[i]->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Wall.png");
        spheres[i]->GetMaterial()->SetSpecularMap(L"Textures/Landscape/Wall_specular.png");
        spheres[i]->GetMaterial()->SetNormalMap(L"Textures/Landscape/Wall_normal.png");

        colliders[i] = new SphereCollider(this->radius);
        colliders[i]->SetParent(spheres[i]);
    }
}

SphereSpawner::~SphereSpawner()
{
    for (auto& sphere : spheres)
    {
        delete sphere;
    }
    spheres.clear();

    for (auto& collider : colliders)
    {
        delete collider;
    }
    colliders.clear();
}

void SphereSpawner::Update()
{
    for (int i = 0; i < COUNT; i++)
    {
        if (isActive[i])
        {
            spheres[i]->UpdateWorld();
            colliders[i]->UpdateWorld();
        }
    }
}

void SphereSpawner::Render()
{
    for (int i = 0; i < COUNT; i++)
    {
        if (isActive[i])
        {
            spheres[i]->Render();
            colliders[i]->Render();
        }
    }
}

bool SphereSpawner::Spawn(Vector3 pos)
{
    for (int i = 0; i < COUNT; i++)
    {
        if (!isActive[i])
        {
            isActive[i] = true;
            spheres[i]->position = pos;
            return true;
        }
    }

    return false;
}

bool SphereSpawner::IsCollided(Collider* collider)
{
    bool isCollided = false;

    for (UINT i = 0; i < COUNT; i++)
    {
        if (!isActive[i])
            continue;

        if (colliders[i]->Collision(collider))
        {
            isCollided = true;
            isActive[i] = false;    // 충돌 판정시 충돌된 구체를 비활성화
        }
    }

    return isCollided;
}

void SphereSpawner::Inactive(UINT index)
{
    isActive[index] = false;
}
