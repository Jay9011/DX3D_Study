#pragma once

class CubeScene : public Scene
{
public:
    CubeScene();
    ~CubeScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void GUIRender() override;

private:
    Quad* quad;
    vector<Cube*> cubes;
};