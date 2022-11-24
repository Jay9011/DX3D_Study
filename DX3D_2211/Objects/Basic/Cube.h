#pragma once

class Cube : public Transform
{
private:
    typedef VertexUV VertexType;

public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    void Render();

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();

private:
    Vector3 size;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Material* material;
    Mesh* mesh;
};