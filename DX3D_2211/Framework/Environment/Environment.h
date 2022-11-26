#pragma once

class Environment : public Singleton<Environment>
{
public:
    Environment();
    ~Environment();

    void GUIRender();

private:
    void CreateProjection();
    void SetViewport();
    void CreateStates();

private:
    MatrixBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;
    LightBuffer* lightBuffer;

    SamplerState* samplerState;

    Vector4 eye = XMVectorSet(128, 50, 0, 0);
    Vector4 focus = XMVectorSet(128, 0, 128, 0);
    Vector4 up = XMVectorSet(0, 1, 0, 0);
};