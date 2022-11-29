#pragma once

class Sphere : public Transform
{
private:
    typedef VertexUVNormal VertexType;

public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere();

    void Render();

    Material* GetMaterial() { return material; }

private:
    void CreateMesh();

private:
    float radius;
    UINT sliceCount, stackCount;

    MatrixBuffer* worldBuffer;

    vector<VertexType> vertices;
    vector<UINT> indices;

    Material* material;
    Mesh* mesh;
};