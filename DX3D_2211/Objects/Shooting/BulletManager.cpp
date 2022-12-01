#include "Framework.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    for (Bullet* bullet : bullets)
        delete bullet;
}

void BulletManager::Update()
{
    for (Bullet* bullet : bullets)
        bullet->Update();
}

void BulletManager::Render()
{
    for (Bullet* bullet : bullets)
        bullet->Render();
}

void BulletManager::Fire(Vector3 pos, Vector3 dir)
{
    for (Bullet* bullet : bullets)
    {
        if (!bullet->Active())
        {
            bullet->Fire(pos, dir);
            return;
        }
    }
}

void BulletManager::CreateBullet(UINT poolCount)
{
    bullets.resize(poolCount);

    for (Bullet*& bullet : bullets)
    {
        bullet = new Bullet();
    }
}

bool BulletManager::Collision(Collider* collider)
{
    for (Bullet* bullet : bullets)
    {
        if (bullet->GetCollider()->Collision(collider))
        {
            bullet->isActive = false;
            return true;
        }
    }

    return false;
}
