#include "Framework.h"
#include "TargetManager.h"

TargetManager::TargetManager()
{
}

TargetManager::~TargetManager()
{
    for (Target* target : targets)
        delete target;
}

void TargetManager::Update()
{
    Spawn();

    for (Target* target : targets)
        target->Update();
}

void TargetManager::Render()
{
    for (Target* target : targets)
        target->Render();
}

void TargetManager::Spawn()
{
    time += DELTA;

    if (time > SPAWN_TIME)
    {
        time -= SPAWN_TIME;

        for (Target* target : targets)
        {
            if (!target->Active())
            {
                target->isActive = true;

                Vector3 pos;
                pos.x = Random(0.f, terrain->GetSize().x);
                pos.z = Random(0.f, terrain->GetSize().y);

                float scale = Random(MIN_SIZE, MAX_SIZE);

                pos.y = terrain->GetHeight(pos) + scale * 0.5f;

                target->position = pos;
                target->scale *= scale;

                return;
            }
        }
    }
}
