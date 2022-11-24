#include "Framework.h"

Quad::Quad(float width, float height) :
    width(width),
    height(height)
{
    material = new Material(L"Shaders/Texture.hlsl");

    CreateMesh();

    worldBuffer = new MatrixBuffer();
}

Quad::~Quad()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void Quad::Render()
{
    worldBuffer->Set(world);
    worldBuffer->SetVSBuffer(0);

    mesh->IASet();
    material->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}

void Quad::CreateMesh()
{
    Float2 halfSize = { width * 0.5f, height * 0.5f };

    vertices.resize(4);
    vertices[0] = VertexType(-halfSize.x, +halfSize.y, 0, 0, 0);
    vertices[1] = VertexType(+halfSize.x, +halfSize.y, 0, 1, 0);
    vertices[2] = VertexType(-halfSize.x, -halfSize.y, 0, 0, 1);
    vertices[3] = VertexType(+halfSize.x, -halfSize.y, 0, 1, 1);

    indices = { 0, 1, 2, 2, 1, 3 };

    mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
