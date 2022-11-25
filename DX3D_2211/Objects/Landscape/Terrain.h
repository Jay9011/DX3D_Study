#pragma once

class Terrain : public Transform
{
private:
    typedef VertexUVNormal VertexType;
    const float MAX_HEIGHT = 20.0f;

public:
    Terrain();
    ~Terrain();

    void Render();

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();
    void CreateNormal();

private:
    UINT width = 10, height = 10;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Material* material;
    Mesh* mesh;

    Texture* heightMap;
};