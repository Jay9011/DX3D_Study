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

void BulletManager::Fire(Vector3 pos, Vector3 dir, Bullet::TYPE owner)
{
    for (Bullet* bullet : bullets)
    {
        if (!bullet->Active())
        {
            bullet->SetOwner(owner);
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

bool BulletManager::Collision(Collider* collider, Bullet::TYPE passType)
{
    for (Bullet* bullet : bullets)
    {
        if (passType == bullet->GetBulletType())    // 총알을 발사한 소유자와 총알의 타입이 같은 경우 넘어감
            continue;

        if (bullet->GetCollider()->Collision(collider))
        {
            bullet->isActive = false;
            return true;
        }
    }

    return false;
}
