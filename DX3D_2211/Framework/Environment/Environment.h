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
};