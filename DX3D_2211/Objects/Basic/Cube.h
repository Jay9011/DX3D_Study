#pragma once

class Cube
{
private:
    typedef VertexColor VertexType;

public:
    Cube();
    Cube(Vector3 size);
    ~Cube();

    void Update();
    void Render();

private:
    void CreateMesh();

private:
    Vector3 size;
    float  rotationSpeed;
    float  angle = 0.0f;
    Float3 translation;

    VertexShader* vertexShader;
    PixelShader* pixelShader;

    MatrixBuffer* worldBuffer;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    Matrix world;
};