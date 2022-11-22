#pragma once

class Cube
{
public:
    Cube();
    Cube(Float3 pos);
    Cube(Float3 pos, float size);
    ~Cube();

    void Update();
    void Render();

private:
    void SetVertex(float size);

private:
    MatrixBuffer* worldBuffer;

    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    VertexShader* vertexShader;
    PixelShader* pixelShader;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    Matrix world;

    Float3 position;
};