#include "Framework.h"

Camera::Camera()
{
    viewBuffer = new ViewBuffer();
    view = XMMatrixIdentity();
}

Camera::~Camera()
{
    delete viewBuffer;
}

void Camera::Update()
{
    FreeMode();
    //FPSMode();
}

void Camera::GUIRender()
{
    if (ImGui::TreeNode("CameraOption"))
    {
        ImGui::InputFloat3("CamPos", (float*)&position, "%.0f");
        ImGui::InputFloat3("CamRot", (float*)&rotation, "%.0f");
        ImGui::DragFloat("CamMoveSpeed", &moveSpeed, 0.1f, 0.0f);
        ImGui::DragFloat("CamRotSpeed", &rotSpeed, 0.1f, 0.0f);

        ImGui::TreePop();
    }
}

void Camera::SetViewBuffer()
{
    viewBuffer->SetVSBuffer(1);
}

void Camera::FreeMode()
{
    if (MOUSE_PRESS(1))
    {
        if (KEY_PRESS('W'))
        {
            position += Forward() * moveSpeed * DELTA;
        }
        if (KEY_PRESS('S'))
        {
            position -= Forward() * moveSpeed * DELTA;
        }
        if (KEY_PRESS('D'))
        {
            position += Right() * moveSpeed * DELTA;
        }
        if (KEY_PRESS('A'))
        {
            position -= Right() * moveSpeed * DELTA;
        }
        if (KEY_PRESS('Q'))
        {
            position -= Up() * moveSpeed * DELTA;
        }
        if (KEY_PRESS('E'))
        {
            position += Up() * moveSpeed * DELTA;
        }

        ImVec2 delta = ImGui::GetIO().MouseDelta;
        rotation.x += delta.y * rotSpeed * DELTA;
        rotation.y += delta.x * rotSpeed * DELTA;
    }

    UpdateWorld();
    view = XMMatrixInverse(nullptr, world);
    viewBuffer->Set(view, world);
}

void Camera::FPSMode()
{
    if (KEY_PRESS('W'))
    {
        position += Forward() * moveSpeed * DELTA;
    }
    if (KEY_PRESS('S'))
    {
        position -= Forward() * moveSpeed * DELTA;
    }
    if (KEY_PRESS('D'))
    {
        position += Right() * moveSpeed * DELTA;
    }
    if (KEY_PRESS('A'))
    {
        position -= Right() * moveSpeed * DELTA;
    }

    if (MOUSE_PRESS(1))
    {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        rotation.x += delta.y * rotSpeed * DELTA;
        rotation.y += delta.x * rotSpeed * DELTA;
    }

    UpdateWorld();
    view = XMMatrixInverse(nullptr, world);
    viewBuffer->Set(view, world);
}
