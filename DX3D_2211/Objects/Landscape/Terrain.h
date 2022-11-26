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

    float GetHeight(Vector3 position);

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();
    void CreateNormal();

private:
    UINT width = 10, height = 10;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Mesh* mesh;
    Material* material;

    Texture* heightMap;
};