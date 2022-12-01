#pragma once

class Terrain : public Transform
{
private:
    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = 20.0f;

public:
    Terrain();
    ~Terrain();

    void Render();

    float GetHeight(Vector3 position);

    Material* GetMaterial() { return material; }
    
    UINT GetWidth() { return width; }
    UINT GetLength() { return height; }
    Float2 GetSize() { return Float2(width, height); }

private:
    void CreateMesh();
    void CreateNormal();
    void CreateTangent();

private:
    UINT width = 10, height = 10;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Mesh* mesh;
    Material* material;

    Texture* heightMap;
};