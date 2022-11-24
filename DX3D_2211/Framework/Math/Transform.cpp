#include "Framework.h"
#include "Transform.h"

Transform::Transform()
    : scale(1, 1, 1), parent(nullptr), isActive(true), tag("untagged")
{
    world = XMMatrixIdentity();    
}

Transform::~Transform()
{    
}

void Transform::UpdateWorld()
{
    world = XMMatrixTransformation(pivot.data, XMQuaternionIdentity(),
        scale.data, pivot.data,
        XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z),
        position.data);

    if (parent != nullptr)
        world *= *parent;

    XMMatrixDecompose(&globalScale.data, &globalRotation.data, &globalPosition.data, world);
}

void Transform::PostRender()
{
    /*if (ImGui::TreeNode(tag.c_str()))
    {
        ImGui::Checkbox(tag.c_str(), &isActive);
        ImGui::DragFloat3((tag + ":Pos").c_str(), (float*)&position, 0.1f);

        Vector3 degree = rotation * 180.0f / XM_PI;
        ImGui::DragFloat3((tag + ":Rot").c_str(), (float*)&degree, 0.1f);
        rotation = degree * XM_PI / 180.0f;

        ImGui::DragFloat3((tag + ":Scale").c_str(), (float*)&scale, 0.1f);

        if (ImGui::Button("Save"))
            Save();
        ImGui::SameLine();
        if (ImGui::Button("Load"))
            Load();

        ImGui::TreePop();
    }*/
}

Vector3 Transform::Right()
{
    Vector3 temp(1, 0, 0);
    return XMVector3Normalize(XMVector3TransformNormal(temp.data, world));
}

Vector3 Transform::Up()
{
    Vector3 temp(0, 1, 0);
    return XMVector3Normalize(XMVector3TransformNormal(temp.data, world));
}

Vector3 Transform::Forward()
{
    Vector3 temp(0, 0, 1);
    return XMVector3Normalize(XMVector3TransformNormal(temp.data, world));
}

void Transform::Save()
{    
    BinaryWriter w("TextData/Transform/" + tag + ".trf");

    w.Vector(position);
    w.Vector(rotation);
    w.Vector(scale);
}

void Transform::Load()
{
    BinaryReader r("TextData/Transform/" + tag + ".trf");

    if (r.IsFailed()) return;

    position = r.Vector();
    rotation = r.Vector();
    scale = r.Vector();
}
