#pragma once

class Target : public Cube
{
public:
    Target();
    ~Target();

    void Update();
    void Render();

private:
    float hp;

    Collider* collider;

};