#pragma once

class Environment : public Singleton<Environment>
{
public:
    Environment();
    ~Environment();

    void Set();
    void PostSet();
    void GUIRender();

    Matrix GetProjection() { return projection; }

    Camera* GetMainCamera() { return mainCamera; }

private:
    void CreateProjection();
    void SetViewport();
    void CreateStates();

private:
    Camera* mainCamera;

    ViewBuffer* uiViewBuffer;

    MatrixBuffer* projectionBuffer;
    MatrixBuffer* orthographicBuffer;

    LightBuffer* lightBuffer;
    
    SamplerState* samplerState;
    BlendState* blendState;

    Matrix projection;
};