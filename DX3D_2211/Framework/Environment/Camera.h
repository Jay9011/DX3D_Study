#pragma once

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void GUIRender();

    void SetViewBuffer();

private:
    void FreeMode();
    void FPSMode();

private:
    float moveSpeed = 50.0f;
    float rotSpeed = 10.0f;

    ViewBuffer* viewBuffer;
    Matrix view;
};