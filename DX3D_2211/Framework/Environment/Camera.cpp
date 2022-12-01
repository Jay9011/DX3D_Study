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

Vector3 Camera::WorldToScreenPoint(Vector3 worldPos)
{
    Vector3 screenPos;

    Matrix projection = Environment::Get()->GetProjection();

    screenPos = XMVector3TransformCoord(worldPos, view);
    screenPos = XMVector3TransformCoord(screenPos, projection);
    // NDC = -1 ~ 1
    // Screen = 0 ~ win_width

    screenPos.x = (screenPos.x + 1.0f) * 0.5f * WIN_WIDTH;
    screenPos.y = (screenPos.y + 1.0f) * 0.5f * WIN_HEIGHT;

    return screenPos;
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
