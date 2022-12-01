#pragma once

class Bullet : public Sphere
{
private:
    const float LIFE_TIME = 5.0f;

public:
    enum TYPE {
        PLAYER_BULLET,
        ENEMY_BULLET
    };

public:
    Bullet();
    ~Bullet();

    void Update();
    void Render();

    void Fire(Vector3 pos, Vector3 direction);

    Collider* GetCollider() { return collider; }

    void SetOwner(Bullet::TYPE owner) { bulletType = owner; }
    Bullet::TYPE GetBulletType() { return bulletType; }

private:
    float speed = 100.0f;
    float time = 0.0f;

    Vector3 direction;

    Collider* collider;

    Bullet::TYPE bulletType = Bullet::PLAYER_BULLET;
};