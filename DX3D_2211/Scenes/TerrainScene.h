#pragma once

class TerrainScene : public Scene
{
public:
    TerrainScene();
    ~TerrainScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void GUIRender() override;

private:
    Terrain* terrain;

    RasterizerState* rasterizerState;
};