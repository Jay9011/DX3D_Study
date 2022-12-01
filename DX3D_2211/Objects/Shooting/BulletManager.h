#pragma once

class BulletManager : public Singleton<BulletManager>
{
public:
    BulletManager();
    ~BulletManager();

    void Update();
    void Render();

    void Fire(Vector3 pos, Vector3 dir);

    void CreateBullet(UINT poolCount = 30);

private:
    vector<Bullet*> bullets;

};