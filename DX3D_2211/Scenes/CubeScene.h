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
    Cube* cube1;
    Cube* cube2;
};