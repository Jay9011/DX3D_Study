#include "Framework.h"
#include "Target.h"

Target::Target()
{
    collider = new SphereCollider();
    collider->SetParent(this);

    isActive = false;

    hpBarBackImg = Texture::Add(L"Textures/UI/hp_bar_BG.png");
    hpBar = new Quad(hpBarBackImg->Width(), hpBarBackImg->Height());
    hpBar->GetMaterial()->SetShader(L"Shaders/Practice/HpBar.hlsl");
    hpBar->GetMaterial()->SetDiffuseMap(L"Textures/UI/hp_bar.png");

    valueBuffer = new FloatValueBuffer();
    valueBuffer->values[0] = 1.0f;
}

Target::~Target()
{
    delete collider;
    delete hpBar;
    delete valueBuffer;
}

void Target::Update()
{
    if (!Active())
        return;

    FireControl();

    hpBar->position = CAM->WorldToScreenPoint(position + Vector3(0.f, 2.f, 0.f));
    hpBar->UpdateWorld();

    UpdateWorld();
    collider->UpdateWorld();
}

void Target::Render()
{
    if (!Active())
        return;

    Cube::Render();
    collider->Render();
}

void Target::PostRender()
{
    if (!Active())
        return;

    valueBuffer->SetPSBuffer(0);
    hpBarBackImg->PSSet(1);
    hpBar->Render();
}

bool Target::Damage(float value)
{
    bool isDead = false;

    curHp -= value;

    if ((int)curHp <= 0)
    {
        isActive = false;
        isDead = true;
    }

    SetHpBar();

    return isDead;
}

void Target::SetHpBar()
{
    valueBuffer->values[0] = curHp / maxHp;
}

void Target::TurnActive()
{
    curHp = maxHp;
    SetHpBar();

    isActive = true;
}

void Target::FireControl()
{
    reloadTimer += DELTA;

    if (reloadTimer >= RELOAD_TIME)
    {
        reloadTimer -= RELOAD_TIME;
        BulletManager::Get()->Fire(position, (CAM->position - position).Normalized(), Bullet::ENEMY_BULLET);
    }
}
