#pragma once

class Cube : public Transform
{
private:
    typedef VertexUV VertexType;

public:
    Cube(Vector3 size = Vector3(1, 1, 1));
    ~Cube();

    //void Update();
    void Render();

    Material* GetMaterial() { return material; }

    void SetScale(Vector3 scale);
    void SetRotateSpeed(float speed);
    void SetPos(Vector3 pos);

private:
    void CreateMesh();

private:
    Vector3 size;

    Vector3 scale;
    float   rotationSpeed;
    Vector3 translation;
    
    vector<VertexType> vertices;
    vector<UINT> indices;

    Material* material;
    Mesh* mesh;

    /*Matrix world;
    MatrixBuffer* worldBuffer;
    Float4x4 worldMatrix;*/
};