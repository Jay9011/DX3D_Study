#pragma once

class BulletManager : public Singleton<BulletManager>
{
private:
    friend class Singleton;

    BulletManager();
    ~BulletManager();

public:
    void Update();
    void Render();

    void Fire(Vector3 pos, Vector3 dir, Bullet::TYPE owner);

    void CreateBullet(UINT poolCount = 50);

    bool Collision(Collider* collider, Bullet::TYPE passType);

private:
    vector<Bullet*> bullets;

};