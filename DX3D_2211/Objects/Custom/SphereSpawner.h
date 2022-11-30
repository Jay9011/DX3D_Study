#pragma once

class SphereSpawner
{
private:
    const UINT COUNT;

public:
    SphereSpawner(float radius = 10.0f, UINT poolCount = 10);
    ~SphereSpawner();

    void Update();
    void Render();

    bool Spawn(Vector3 pos);
    bool IsCollided(Collider* collider);
    void Inactive(UINT index);

    float GetRadius() { return radius; }

private:
    float radius;

    vector<Sphere*> spheres;
    vector<Collider*> colliders;
    vector<bool> isActive;
};