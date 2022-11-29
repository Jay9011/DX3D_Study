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

private:
    void FirstPersonView();

private:
    Terrain* terrain;
    SphereManager* sphereMgr;
    Quad* crosshair;
};