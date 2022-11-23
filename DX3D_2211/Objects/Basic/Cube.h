#pragma once

class Cube
{
public:
    Cube();
    Cube(Float3 pos);
    Cube(Float3 pos, float size);
    Cube(Float3 pos, float size, float speed);
    ~Cube();

    void Update();
    void Render();

private:
    void SetVertex();

private:
    MatrixBuffer* worldBuffer;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    VertexShader* vertexShader;
    PixelShader* pixelShader;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    Matrix world;

    float  scale;
    float  rotationSpeed;
    float  angle = 0.0f;
    Float3 translation;
};