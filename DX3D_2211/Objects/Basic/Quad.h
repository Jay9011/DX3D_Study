#pragma once

class Quad : public Transform
{
private:
    typedef VertexUV VertexType;

public:
    Quad(float width = 1.0f, float height = 1.0f);
    ~Quad();

    void Render();

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();

private:
    float width, height;

    MatrixBuffer* worldBuffer;

    Material* material;
    Mesh* mesh;

    vector<VertexType> vertices;
    vector<UINT> indices;

    BlendState* blendState[2];
};