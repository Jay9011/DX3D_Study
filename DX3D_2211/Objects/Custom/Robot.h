#pragma once

class Robot
{
private:
    enum Part
    {
        HEAD,
        BODY,
        LEFT_UPPER_ARM,
        LEFT_LOWER_ARM,
        RIGHT_UPPER_ARM,
        RIGHT_LOWER_ARM,
        LEFT_UPPER_LEG,
        LEFT_LOWER_LEG,
        RIGHT_UPPER_LEG,
        RIGHT_LOWER_LEG,
        END
    };

public:
    Robot();
    ~Robot();

    void Update();
    void Render();

private:
    void Move();

    void CreateParts();
    Vector3 GetPartSize(Part part);
    void SetPartPos();

    void ShakeHand();
    void ShakeLeg();

private:
    Transform* root;
    Quad* face;
    vector<Cube*> parts;

    float moveSpeed = 0.005f;
    float spinSpeed = 0.001f;
    float partRotationSpeed = 0.001f;

    Vector3 sizeFace = Vector3(0.7f, 0.7f, 0.f);
    Vector3 sizeHead = Vector3(1.f, 1.f, 1.f);
    Vector3 sizeBody = Vector3(1.5f, 2.f, 1.f);
    Vector3 sizeUpperArm = Vector3(0.6f, 1.3f, 0.6f);
    Vector3 sizeLowerArm = Vector3(0.5f, 1.3f, 0.5f);
    Vector3 sizeUpperLeg = Vector3(0.75f,1.3f, 0.75f);
    Vector3 sizeLowerLeg = Vector3(0.5f, 1.3f, 0.5f);
};