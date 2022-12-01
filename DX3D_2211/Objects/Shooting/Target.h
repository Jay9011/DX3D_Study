#pragma once

class Target : public Cube
{
public:
    Target();
    ~Target();

    void Update();
    void Render();
    void PostRender();

    Collider* GetCollider() { return collider; }

private:
    float hp;

    Collider* collider;
    Quad* hpBar;
};