#include "Framework.h"
#include "Player.h"

Player::Player()
{
    crosshair = new Quad(70.f, 70.f);
    crosshair->GetMaterial()->SetDiffuseMap(L"Textures/UI/cursor.png");
    crosshair->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
    crosshair->UpdateWorld();

    hpBarBackImg = Texture::Add(L"Textures/UI/hp_bar_BG.png");
    hpBar = new Quad(HPBAR_WIDTH, HPBAR_HEIGHT);
    hpBar->GetMaterial()->SetShader(L"Shaders/Practice/HpBar.hlsl");
    hpBar->GetMaterial()->SetDiffuseMap(L"Textures/UI/hp_bar.png");
    hpBar->position = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.1f, 0.0f };
    hpBar->UpdateWorld();

    valueBuffer = new FloatValueBuffer();
    valueBuffer->values[0] = 1.0f;

    collider = new SphereCollider();
    collider->SetParent(CAM);
}

Player::~Player()
{
    delete crosshair;
    delete hpBar;
    delete valueBuffer;
    delete collider;
}

void Player::Update()
{
    MoveControl();
    FireControl();
    CollisionTarget();
    collider->UpdateWorld();
    CollisionBullet();
}

void Player::Render()
{
    //collider->Render();
}

void Player::PostRender()
{
    crosshair->Render();

    valueBuffer->SetPSBuffer(0);
    hpBarBackImg->PSSet(1);
    hpBar->Render();
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
    if (MOUSE_PRESS(1))
    {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        cam->rotation.x += delta.y * rotSpeed * DELTA;
        cam->rotation.y += delta.x * rotSpeed * DELTA;
    }
}

void Player::FireControl()
{
    if (MOUSE_DOWN(0))
    {
        BulletManager::Get()->Fire(CAM->position, CAM->Forward(), Bullet::PLAYER_BULLET);
    }
}

void Player::CollisionTarget()
{
    Target* target = TargetManager::Get()->CollisionBullet();

    if (target)
    {
        if (target->Damage(1.0f))   // ÀûÀÌ Á×Àº °æ¿ì true ¹ÝÈ¯µÊ
            score += 1.0f;
    }
}

void Player::CollisionBullet()
{
    if (BulletManager::Get()->Collision(collider, Bullet::PLAYER_BULLET))
    {
        curHp -= 1.0f;
        SetHpBar();
    }
}

void Player::SetHpBar()
{
    valueBuffer->values[0] = curHp / maxHp;
}
