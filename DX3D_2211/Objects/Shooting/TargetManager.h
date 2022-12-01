#pragma once

class TargetManager : public Singleton<TargetManager>
{
private:
    friend class Singleton;

    const float SPAWN_TIME = 3.0f;
    const float MIN_SIZE = 1.0f;
    const float MAX_SIZE = 5.0f;

    TargetManager();
    ~TargetManager();

public:
    void Update();
    void Render();
    void PostRender();

    void CreateTargets(UINT poolCount = 50);

    Target* CollisionBullet();

    void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

private:
    void Spawn();

private:
    vector<Target*> targets;

    float time = 0.0f;

    Terrain* terrain;
};