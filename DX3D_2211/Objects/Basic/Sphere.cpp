#include "Framework.h"

Sphere::Sphere(float radius, UINT sliceCount, UINT stackCount) :
    radius(radius),
    sliceCount(sliceCount),
    stackCount(stackCount)
{
    material = new Material(L"Shaders/Specular.hlsl");

    CreateMesh();

    worldBuffer = new MatrixBuffer();
}

Sphere::~Sphere()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void Sphere::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVSBuffer(0);

    mesh->IASet();
    material->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Sphere::CreateMesh()
{
    float phiStep = XM_PI / stackCount;
    float thetaStep = XM_2PI / sliceCount;

    vertices.resize((sliceCount + 1) * (stackCount + 1));

    // Vertices
    for (UINT i = 0; i <= stackCount; i++)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            VertexType vertex;

            vertex.normal.x = sin(phi) * cos(theta);
            vertex.normal.y = cos(phi);
            vertex.normal.z = sin(phi) * sin(theta);

            vertex.pos = Vector3(vertex.normal) * radius;

            vertex.uv.x = j / (float)sliceCount;
            vertex.uv.y = i / (float)stackCount;

            UINT index = (sliceCount + 1) * i + j;
            vertices[index] = vertex;
        }
    }

    // Indices
    indices.resize(stackCount * sliceCount * 6);

    UINT index = 0;
    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            indices[index++] = (sliceCount + 1) * i + j;        // 0
            indices[index++] = (sliceCount + 1) * i + j + 1;    // 1
            indices[index++] = (sliceCount + 1) * (i + 1) + j;  // 2

            indices[index++] = (sliceCount + 1) * (i + 1) + j;      // 2
            indices[index++] = (sliceCount + 1) * i + j + 1;        // 1
            indices[index++] = (sliceCount + 1) * (i + 1) + j + 1;  // 3
        }
    }

    mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
