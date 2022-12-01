#pragma once

class Target : public Cube
{
private:
    const float RELOAD_TIME = 3.0f;

public:
    Target();
    ~Target();

    void Update();
    void Render();
    void PostRender();

    Collider* GetCollider() { return collider; }

    bool Damage(float value);
    void SetHpBar();
    void TurnActive();
    void FireControl();

private:
    float maxHp = 3.0f;
    float curHp = 3.0f;
    float reloadTimer = 0.0f;

    Collider* collider;
    Quad* hpBar;

    FloatValueBuffer* valueBuffer;
    Texture* hpBarBackImg;
};