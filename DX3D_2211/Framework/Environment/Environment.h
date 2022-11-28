#pragma once

class Environment : public Singleton<Environment>
{
public:
    Environment();
    ~Environment();

    void Set();
    void GUIRender();

    Camera* GetMainCamera() { return mainCamera; }

private:
    void CreateProjection();
    void SetViewport();
    void CreateStates();

private:
    Camera* mainCamera;
    MatrixBuffer* projectionBuffer;
    LightBuffer* lightBuffer;

    SamplerState* samplerState;
};