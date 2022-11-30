#include "Framework.h"

Collider::Collider()
{
    material = new Material(L"Shaders/Collider.hlsl");    
    worldBuffer = new MatrixBuffer();

    SetColor(0, 1, 0);
}

Collider::~Collider()
{
    delete material;
    delete mesh;
    delete worldBuffer;
}

void Collider::Render()
{
    if (!isActive) return;

    worldBuffer->Set(world);
    worldBuffer->SetVSBuffer(0);

    mesh->IASet(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    material->Set();

    DC->DrawIndexed(indices.size(), 0, 0);
}

bool Collider::Collision(Collider* collider)
{
    if (!isActive) return false;
    if (!collider->isActive) return false;

    UpdateWorld();
    collider->UpdateWorld();

    switch (collider->type)
    {
    case Collider::BOX:
        return BoxCollision((BoxCollider*)collider);
        break;
    case Collider::SPHERE:
        return SphereCollision((SphereCollider*)collider);
        break;
    case Collider::CAPSULE:
        return CapsuleCollision((CapsuleCollider*)collider);
        break;    
    }

    return false;
}

void Collider::CreateMesh()
{
    mesh = new Mesh(vertices.data(), sizeof(Vertex), vertices.size(),
        indices.data(), indices.size());
}
