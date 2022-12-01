#pragma once

class Bullet : public Sphere
{
private:
    const float LIFE_TIME = 5.0f;

public:
    Bullet();
    ~Bullet();

    void Update();
    void Render();

    void Fire(Vector3 pos, Vector3 direction);

    Collider* GetCollider() { return collider; }

private:
    float speed = 50.0f;
    float time = 0.0f;

    Vector3 direction;

    Collider* collider;

};