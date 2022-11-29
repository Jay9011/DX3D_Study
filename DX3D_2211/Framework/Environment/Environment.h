#pragma once

class Environment : public Singleton<Environment>
{
public:
    Environment();
    ~Environment();

    void Set();
    void PostSet();
    void GUIRender();

    Camera* GetMainCamera() { return mainCamera; }

private:
    void CreateProjection();
    void SetViewport();
    void CreateStates();

private:
    Camera* mainCamera;

    MatrixBuffer* projectionBuffer;
    MatrixBuffer* orthographicBuffer;

    MatrixBuffer* uiViewBuffer;

    LightBuffer* lightBuffer;
    
    SamplerState* samplerState;
    BlendState* blendState;
};