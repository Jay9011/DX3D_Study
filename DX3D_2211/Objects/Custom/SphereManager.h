#pragma once

class SphereManager
{
private:
    const UINT SIZE;

public:
    SphereManager(UINT poolCount = 10);
    ~SphereManager();

    void Update();
    void Render();

    void Shoot(Vector3 pos, Vector3 dir);

private:
    vector<Sphere*> spheres;
    vector<bool> isActive;
    vector<Vector3> dir;

    float speed = 0.5f;
};