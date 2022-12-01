#include "Framework.h"
#include "Player.h"

Player::Player()
{
    crosshair = new Quad(100.f, 100.f);
    crosshair->GetMaterial()->SetDiffuseMap(L"Textures/UI/cursor.png");
    crosshair->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
    crosshair->UpdateWorld();
}

Player::~Player()
{
    delete crosshair;
}

void Player::Update()
{
    MoveControl();
    FireControl();
}

void Player::PostRender()
{
    crosshair->Render();
}

void Player::MoveControl()
{
    Camera* cam = CAM;
    
    if (KEY_PRESS('W'))
    {
        Vector3 forward = cam->Forward();
        forward.y = 0.0f;
        forward.Normalized();
        cam->position += forward * moveSpeed * DELTA;
    }
    if (KEY_PRESS('S'))
    {
        Vector3 forward = cam->Forward();
        forward.y = 0.0f;
        forward.Normalized();
        cam->position -= forward * moveSpeed * DELTA;
    }
    if (KEY_PRESS('D'))
    {
        Vector3 right = cam->Right();
        right.y = 0.0f;
        right.Normalized();
        cam->position += right * moveSpeed * DELTA;
    }
    if (KEY_PRESS('A'))
    {
        Vector3 right = cam->Right();
        right.y = 0.0f;
        right.Normalized();
        cam->position -= right * moveSpeed * DELTA;
    }

    cam->position.y = terrain->GetHeight(cam->position) + height;

    ImVec2 delta = ImGui::GetIO().MouseDelta;
    cam->rotation.x += delta.y * rotSpeed * DELTA;
    cam->rotation.y += delta.x * rotSpeed * DELTA;
}

void Player::FireControl()
{
    if (MOUSE_DOWN(0))
    {
        BulletManager::Get()->Fire(CAM->position, CAM->Forward());
    }
}
