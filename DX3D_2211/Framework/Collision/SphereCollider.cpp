#include "Framework.h"

SphereCollider::SphereCollider(float radius, UINT stackCount, UINT sliceCount) :
    radius(radius)
{
    type = SPHERE;

    float phiStep = XM_PI / stackCount;
    float thetaStep = XM_2PI / sliceCount;

    //Vertices
    for (UINT i = 0; i <= stackCount; i++)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            Vertex vertex;

            vertex.pos.x = sin(phi) * cos(theta) * radius;
            vertex.pos.y = cos(phi) * radius;
            vertex.pos.z = sin(phi) * sin(theta) * radius;

            vertices.push_back(vertex);
        }
    }

    //Indices
    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * i + j + 1);//1            

            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * (i + 1) + j);//2            
        }
    }

    CreateMesh();
}

bool SphereCollider::RayCollision(IN Ray ray, OUT Contact* contact)
{
    return false;
}

bool SphereCollider::BoxCollision(BoxCollider* collider)
{
    return false;
}

bool SphereCollider::SphereCollision(SphereCollider* collider)
{
    return false;
}

bool SphereCollider::CapsuleCollision(CapsuleCollider* collider)
{
    return false;
}
