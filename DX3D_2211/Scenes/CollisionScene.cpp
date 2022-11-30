#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
    Collider* collider = new SphereCollider();
    collider->tag = "Sphere1";
    colliders.push_back(collider);
    
    collider = new SphereCollider();
    collider->tag = "Sphere2";
    colliders.push_back(collider);
}

CollisionScene::~CollisionScene()
{
    for (Collider* collider : colliders)
        delete collider;
}

void CollisionScene::Update()
{
    for (Collider* collider : colliders)
        collider->UpdateWorld();
}

void CollisionScene::Render()
{
    for (Collider* collider : colliders)
        collider->Render();
}

void CollisionScene::PostRender()
{
    
}

void CollisionScene::GUIRender()
{
    for (Collider* collider : colliders)
        collider->PostRender();
}
