#include "Framework.h"

Robot::Robot()
{
    
    CreateParts();
    SetPartPos();

}

Robot::~Robot()
{
    delete face;

    for (auto& part : parts)
        delete part;

    parts.clear();
}

void Robot::Update()
{
    Move();

    face->UpdateWorld();

    for (auto& part : parts)
        part->UpdateWorld();

}

void Robot::Render()
{
    face->Render();

    for (auto& part : parts)
        part->Render();
}

void Robot::Move()
{
    if (GetAsyncKeyState('W'))
    {
        ShakeHand();
        ShakeLeg();
        parts[(int)Part::BODY]->position -= parts[(int)Part::BODY]->Forward() * moveSpeed;
    }
    else if (GetAsyncKeyState('S'))
    {
        ShakeHand();
        ShakeLeg();
        parts[(int)Part::BODY]->position += parts[(int)Part::BODY]->Forward() * moveSpeed;
    }

    if (GetAsyncKeyState('A'))
    {
        parts[(int)Part::BODY]->rotation.y -= spinSpeed;
    }
    else if (GetAsyncKeyState('D'))
    {
        parts[(int)Part::BODY]->rotation.y += spinSpeed;
    }

}

void Robot::ShakeHand()
{
    static bool leftHandForward = true;
    static bool rightHandForward = false;

    float leftUpperArmRX = parts[(int)Part::LEFT_UPPER_ARM]->rotation.x;
    float rightUpperArmRX = parts[(int)Part::RIGHT_UPPER_ARM]->rotation.x;
    float leftLowerArmRX = parts[(int)Part::LEFT_LOWER_ARM]->rotation.x;
    float rightLowerArmRX = parts[(int)Part::RIGHT_LOWER_ARM]->rotation.x;

    if (leftHandForward)
    {
        parts[(int)Part::LEFT_UPPER_ARM]->rotation.x += partRotationSpeed;
        parts[(int)Part::LEFT_LOWER_ARM]->rotation.x += partRotationSpeed;
    }
    else
    {
        parts[(int)Part::LEFT_UPPER_ARM]->rotation.x -= partRotationSpeed;

        if(leftLowerArmRX > 0)
            parts[(int)Part::LEFT_LOWER_ARM]->rotation.x -= partRotationSpeed;
    }
    
    if (rightHandForward)
    {
        parts[(int)Part::RIGHT_UPPER_ARM]->rotation.x += partRotationSpeed;
        parts[(int)Part::RIGHT_LOWER_ARM]->rotation.x += partRotationSpeed;
    }
    else
    {
        parts[(int)Part::RIGHT_UPPER_ARM]->rotation.x -= partRotationSpeed;

        if(rightLowerArmRX > 0)
            parts[(int)Part::RIGHT_LOWER_ARM]->rotation.x -= partRotationSpeed;
    }

    if ((leftUpperArmRX < -1.0f && !leftHandForward) || (leftUpperArmRX > 1.0f && leftHandForward))
    {
        leftHandForward = !leftHandForward;
    }
    if ((rightUpperArmRX < -1.0f && !rightHandForward) || (rightUpperArmRX > 1.0f && rightHandForward))
    {
        rightHandForward = !rightHandForward;
    }
}

void Robot::ShakeLeg()
{
    static bool leftLegForward = false;
    static bool rightLegForward = true;

    float leftUpperLegRX = parts[(int)Part::LEFT_UPPER_LEG]->rotation.x;
    float rightUpperLegRX = parts[(int)Part::RIGHT_UPPER_LEG]->rotation.x;
    float leftLowerLegRX = parts[(int)Part::LEFT_LOWER_LEG]->rotation.x;
    float rightLowerLegRX = parts[(int)Part::RIGHT_LOWER_LEG]->rotation.x;

    if (leftLegForward)
    {
        parts[(int)Part::LEFT_UPPER_LEG]->rotation.x += partRotationSpeed;
        if(leftLowerLegRX > -1.2f)
            parts[(int)Part::LEFT_LOWER_LEG]->rotation.x -= partRotationSpeed;
    }
    else
    {
        parts[(int)Part::LEFT_UPPER_LEG]->rotation.x -= partRotationSpeed;
        if (leftLowerLegRX < 0)
            parts[(int)Part::LEFT_LOWER_LEG]->rotation.x += partRotationSpeed * 1.5f;
    }

    if (rightLegForward)
    {
        parts[(int)Part::RIGHT_UPPER_LEG]->rotation.x += partRotationSpeed;
        if (rightLowerLegRX > -1.2f)
            parts[(int)Part::RIGHT_LOWER_LEG]->rotation.x -= partRotationSpeed;
    }
    else
    {
        parts[(int)Part::RIGHT_UPPER_LEG]->rotation.x -= partRotationSpeed;
        if (rightLowerLegRX < 0)
            parts[(int)Part::RIGHT_LOWER_LEG]->rotation.x += partRotationSpeed * 1.5f;
    }

    if ((leftUpperLegRX < -1.0f && !leftLegForward) || (leftUpperLegRX > 1.0f && leftLegForward))
    {
        leftLegForward = !leftLegForward;
    }
    if ((rightUpperLegRX < -1.0f && !rightLegForward) || (rightUpperLegRX > 1.0f && rightLegForward))
    {
        rightLegForward = !rightLegForward;
    }
}

void Robot::CreateParts()
{
    face = new Quad(0.7f, 0.7f);
    face->GetMaterial()->SetDiffuseMap(L"Textures/Etc/face.jpg");

    parts.resize((int)Part::END);
    for (int i = 0; i < (int)Part::END; i++)
    {
        parts[i] = new Cube(GetPartSize((Part)i));
        parts[i]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/white.jpg");
    }
    parts[(int)Part::BODY]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/body.jpg");
    parts[(int)Part::LEFT_UPPER_ARM]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/body.jpg");
    parts[(int)Part::RIGHT_UPPER_ARM]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/body.jpg");
    parts[(int)Part::LEFT_UPPER_LEG]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/pants.jpg");
    parts[(int)Part::RIGHT_UPPER_LEG]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/pants.jpg");

    face->SetParent(parts[(int)Part::HEAD]);

    parts[(int)Part::HEAD]->SetParent(parts[(int)Part::BODY]);

    parts[(int)Part::LEFT_UPPER_ARM]->SetParent(parts[(int)Part::BODY]);
    parts[(int)Part::RIGHT_UPPER_ARM]->SetParent(parts[(int)Part::BODY]);
    parts[(int)Part::LEFT_UPPER_LEG]->SetParent(parts[(int)Part::BODY]);
    parts[(int)Part::RIGHT_UPPER_LEG]->SetParent(parts[(int)Part::BODY]);

    parts[(int)Part::LEFT_LOWER_ARM]->SetParent(parts[(int)Part::LEFT_UPPER_ARM]);
    parts[(int)Part::RIGHT_LOWER_ARM]->SetParent(parts[(int)Part::RIGHT_UPPER_ARM]);
    parts[(int)Part::LEFT_LOWER_LEG]->SetParent(parts[(int)Part::LEFT_UPPER_LEG]);
    parts[(int)Part::RIGHT_LOWER_LEG]->SetParent(parts[(int)Part::RIGHT_UPPER_LEG]);
}

Vector3 Robot::GetPartSize(Part part)
{
    Vector3 size;

    switch (part)
    {
    case Part::HEAD:
        size = sizeHead;
        break;
    case Part::BODY:
        size = sizeBody;
        break;
    case Part::LEFT_UPPER_ARM:
        size = sizeUpperArm;
        break;
    case Part::LEFT_LOWER_ARM:
        size = sizeLowerArm;
        break;
    case Part::RIGHT_UPPER_ARM:
        size = sizeUpperArm;
        break;
    case Part::RIGHT_LOWER_ARM:
        size = sizeLowerArm;
        break;
    case Part::LEFT_UPPER_LEG:
        size = sizeUpperLeg;
        break;
    case Part::LEFT_LOWER_LEG:
        size = sizeLowerLeg;
        break;
    case Part::RIGHT_UPPER_LEG:
        size = sizeUpperLeg;
        break;
    case Part::RIGHT_LOWER_LEG:
        size = sizeLowerLeg;
        break;
    }

    return size;
}

void Robot::SetPartPos()
{
    // Set Pivot
    parts[(int)Part::LEFT_UPPER_ARM]->SetPivot(0.0f, sizeUpperArm.y * 0.3f, 0.0f);
    parts[(int)Part::LEFT_LOWER_ARM]->SetPivot(0.0f, sizeLowerArm.y * 0.3f, 0.0f);
    parts[(int)Part::RIGHT_UPPER_ARM]->SetPivot(0.0f, sizeUpperArm.y * 0.3f, 0.0f);
    parts[(int)Part::RIGHT_LOWER_ARM]->SetPivot(0.0f, sizeLowerArm.y * 0.3f, 0.0f);

    parts[(int)Part::LEFT_UPPER_LEG]->SetPivot(0.0f, sizeUpperLeg.y * 0.4f, 0.0f);
    parts[(int)Part::LEFT_LOWER_LEG]->SetPivot(0.0f, sizeLowerLeg.y * 0.4f, 0.0f);
    parts[(int)Part::RIGHT_UPPER_LEG]->SetPivot(0.0f, sizeUpperLeg.y * 0.4f, 0.0f);
    parts[(int)Part::RIGHT_LOWER_LEG]->SetPivot(0.0f, sizeLowerLeg.y * 0.4f, 0.0f);

    // Set Position
    face->position.z -= sizeHead.z * 0.51f;

    parts[(int)Part::BODY]->position = { 0.0f, 0.0f, 0.0f };
    parts[(int)Part::HEAD]->position.y += (sizeBody.y * 0.5f + sizeHead.y * 0.5f);

    parts[(int)Part::LEFT_UPPER_ARM]->position.x += (sizeBody.x * 0.5f + sizeUpperArm.x * 0.5f);
    parts[(int)Part::LEFT_UPPER_ARM]->position.y += sizeBody.x * 0.2f;
    parts[(int)Part::LEFT_LOWER_ARM]->position.y -= (sizeUpperArm.y * 0.5f + sizeLowerArm.y * 0.5f);

    parts[(int)Part::RIGHT_UPPER_ARM]->position.x -= (sizeBody.x * 0.5f + sizeUpperArm.x * 0.5f);
    parts[(int)Part::RIGHT_UPPER_ARM]->position.y += sizeBody.x * 0.2f;
    parts[(int)Part::RIGHT_LOWER_ARM]->position.y -= (sizeUpperArm.y * 0.5f + sizeLowerArm.y * 0.5f);

    parts[(int)Part::LEFT_UPPER_LEG]->position.x += sizeBody.x * 0.25f;
    parts[(int)Part::LEFT_UPPER_LEG]->position.y -= (sizeBody.y * 0.5f + sizeUpperLeg.y * 0.5f);
    parts[(int)Part::LEFT_LOWER_LEG]->position.y -= (sizeUpperLeg.y * 0.5f + sizeLowerLeg.y * 0.5f);

    parts[(int)Part::RIGHT_UPPER_LEG]->position.x -= sizeBody.x * 0.25f;
    parts[(int)Part::RIGHT_UPPER_LEG]->position.y -= (sizeBody.y * 0.5f + sizeUpperLeg.y * 0.5f);
    parts[(int)Part::RIGHT_LOWER_LEG]->position.y -= (sizeUpperLeg.y * 0.5f + sizeLowerLeg.y * 0.5f);
}
