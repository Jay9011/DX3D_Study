#pragma once

class SphereManager
{
private:
    const UINT COUNT;
    const float SPEED = 500.0f;
    const float RADIUS = 1.0f;

public:
    SphereManager(UINT poolCount = 10);
    ~SphereManager();

    void Update();
    void Render();

    void Shoot(Vector3 pos, Vector3 dir);
    void Inactive(UINT index);

    vector<bool>* GetActiveList() { return &isActive; }
    Collider* GetCollider(UINT index) { return colliders[index]; }

private:
    vector<Sphere*> spheres;
    vector<Collider*> colliders;
    vector<bool> isActive;
    vector<Vector3> dir;
};