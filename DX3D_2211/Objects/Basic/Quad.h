#pragma once

class Quad
{
private:
    typedef VertexUV VertexType;

public:
    Quad(float width = 1.0f, float height = 1.0f);
    ~Quad();

    void Update();
    void Render();

private:
    void CreateMesh();

private:
    float width, height;

    MatrixBuffer* worldBuffer;

    Material* material;
    Mesh* mesh;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Matrix world;
};