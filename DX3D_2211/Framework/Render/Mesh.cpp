#include "Framework.h"

Mesh::Mesh(void* vertexData, UINT stride, UINT vertexCount, void* indexData, UINT indexCount)
{
    vertexBuffer = new VertexBuffer(vertexData, stride, vertexCount);
    indexBuffer = new IndexBuffer(indexData, indexCount);
}

Mesh::~Mesh()
{
    delete vertexBuffer;
    delete indexBuffer;
}

void Mesh::IASet(D3D11_PRIMITIVE_TOPOLOGY type)
{
    vertexBuffer->IASet(type);
    indexBuffer->IASet();
}
