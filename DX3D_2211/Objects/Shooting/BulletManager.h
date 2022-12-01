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

    void Fire(Vector3 pos, Vector3 dir);

    void CreateBullet(UINT poolCount = 30);

private:
    vector<Bullet*> bullets;

};