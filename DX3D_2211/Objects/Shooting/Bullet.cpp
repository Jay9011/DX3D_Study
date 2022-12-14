#include "Framework.h"

Bullet::Bullet()
{
    isActive = false;

    collider = new SphereCollider();
    collider->SetParent(this);

    scale *= 0.5f;
}

Bullet::~Bullet()
{
    delete collider;
}

void Bullet::Update()
{
    if (!Active())
        return;

    time += DELTA;
    position += direction * speed * DELTA;

    if (time > LIFE_TIME)
        isActive = false;

    UpdateWorld();
    collider->UpdateWorld();
}

void Bullet::Render()
{
    if (!Active())
        return;

    Sphere::Render();
    collider->Render();
}

void Bullet::Fire(Vector3 pos, Vector3 direction)
{
    time = 0.0f;
    position = pos;
    this->direction = direction;

    UpdateWorld();
    collider->UpdateWorld();

    isActive = true;
}
