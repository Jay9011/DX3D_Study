#include "Framework.h"
#include "SphereManager.h"

SphereManager::SphereManager(UINT poolCount) :
    SIZE(poolCount)
{
    spheres.resize(poolCount);
    isActive.resize(poolCount);
    dir.resize(poolCount);
    for (int i = 0; i < poolCount; i++)
    {
        spheres[i] = new Sphere(10.f);
    }
}

SphereManager::~SphereManager()
{
    for (auto& sphere : spheres)
    {
        delete sphere;
    }
    spheres.clear();
}

void SphereManager::Update()
{
    for (int i = 0; i < SIZE; i++)
    {
        if (isActive[i])
        {
            // 특정 범위를 넘어가면 비활성화
            if (spheres[i]->position.x <= -1000 || spheres[i]->position.x >= 3000 || spheres[i]->position.z <= -1000 || spheres[i]->position.z >= 3000)
                isActive[i] = false;

            spheres[i]->position += dir[i] * speed;
            spheres[i]->UpdateWorld();
        }
    }
}

void SphereManager::Render()
{
    for (int i = 0; i < SIZE; i++)
    {
        if (isActive[i])
        {
            spheres[i]->Render();
        }
    }
}

void SphereManager::Shoot(Vector3 pos, Vector3 dir)
{
    for (int i = 0; i < SIZE; i++)
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
