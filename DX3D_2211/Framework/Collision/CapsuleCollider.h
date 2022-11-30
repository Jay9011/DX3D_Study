#pragma once

class CapsuleCollider : public Collider
{
public:
    CapsuleCollider();

    virtual bool RayCollision(IN Ray ray, OUT Contact* contact) override;
    virtual bool BoxCollision(BoxCollider* collider) override;
    virtual bool SphereCollision(SphereCollider* collider) override;
    virtual bool CapsuleCollision(CapsuleCollider* collider) override;
};