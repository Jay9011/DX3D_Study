#pragma once

class Environment : public Singleton<Environment>
{
public:
    Environment();
    ~Environment();

private:
    void CreateProjection();
    void SetViewport();

private:
    MatrixBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;
};