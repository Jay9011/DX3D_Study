#include "Framework.h"
#include "SphereManager.h"

SphereManager::SphereManager(UINT poolCount) :
    COUNT(poolCount)
{
    spheres.resize(COUNT);
    isActive.resize(COUNT);
    dir.resize(COUNT);
    colliders.resize(COUNT);
    for (int i = 0; i < COUNT; i++)
    {
        spheres[i] = new Sphere(RADIUS);
        spheres[i]->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Stones.png");
        spheres[i]->GetMaterial()->SetNormalMap(L"Textures/Landscape/Stones_normal.png");

        colliders[i] = new SphereCollider(RADIUS);
        colliders[i]->SetParent(spheres[i]);
    }
}

SphereManager::~SphereManager()
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

void SphereManager::Update()
{
    for (int i = 0; i < COUNT; i++)
    {
        if (isActive[i])
        {
            // 특정 범위를 넘어가면 비활성화
            if (spheres[i]->position.x <= -1000 || spheres[i]->position.x >= 3000 || spheres[i]->position.z <= -1000 || spheres[i]->position.z >= 3000)
                isActive[i] = false;

            spheres[i]->position += dir[i] * SPEED * DELTA;
            spheres[i]->UpdateWorld();
            colliders[i]->UpdateWorld();
        }
    }
}

void SphereManager::Render()
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

void SphereManager::Shoot(Vector3 pos, Vector3 dir)
{
    for (int i = 0; i < COUNT; i++)
    {
        if (!isActive[i])
        {
            this->dir[i] = dir;
            isActive[i] = true;
            spheres[i]->position = pos;
            break;
        }
    }
}

void SphereManager::Inactive(UINT index)
{
    isActive[index] = false;
}
