#pragma once

class FirstPersonShooterScene : public Scene
{
private:
    const float VIEW_HEIGHT = 10.0f;

public:
    FirstPersonShooterScene();
    ~FirstPersonShooterScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

    void SphereSpawn();
    void CollideCheck();

private:
    Terrain* terrain;
    Quad* crosshair;

    int terrainWidth = 0, terrainLength = 0;

    SphereManager* sphereMgr;
    SphereSpawner* sphereSpawner;

    vector<bool>* isActiveSphere;
};