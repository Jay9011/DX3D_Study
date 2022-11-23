#pragma once

class Cube
{
private:
    typedef VertexUV VertexType;

public:
    Cube(Vector3 size);
    ~Cube();

    void Update();
    void Render();

    void SetScale(Vector3 scale);
    void SetRotateSpeed(float speed);
    void SetPos(Vector3 pos);

private:
    void CreateMesh();

private:
    Vector3 size;

    Vector3 scale;
    float  angle = 0.0f;
    float  rotationSpeed;
    Vector3 translation;
    
    vector<VertexType> vertices;
    vector<UINT> indices;

    Matrix world;
    MatrixBuffer* worldBuffer;

    Material* material;
    Mesh* mesh;
};