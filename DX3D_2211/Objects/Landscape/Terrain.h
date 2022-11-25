#pragma once

class Terrain : public Transform
{
private:
    typedef VertexUV VertexType;

public:
    Terrain();
    ~Terrain();

    void Render();

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();

private:
    UINT width = 10, height = 10;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Material* material;
    Mesh* mesh;

    Texture* heightMap;
};