#pragma once

class Cube : public Transform
{
private:
    typedef VertexUVNormal VertexType;

public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    void Render();

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();
    void CreateNormal();

private:
    Vector3 size;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Material* material;
    Mesh* mesh;
};