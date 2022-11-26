#include "Framework.h"

Robot::Robot()
{
    root = new Transform(); // 루트 생성
    CreateParts();
    SetPartPos();
}

Robot::~Robot()
{
    delete face;

    for (auto& part : parts)
        delete part;

    parts.clear();

    delete root;
}

void Robot::Update()
{
    Move();

    face->UpdateWorld();

    for (auto& part : parts)
        part->UpdateWorld();

    root->UpdateWorld();
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
        root->position -= root->Forward() * moveSpeed;
    }
    else if (GetAsyncKeyState('S'))
    {
        ShakeHand();
        ShakeLeg();
        root->position += root->Forward() * moveSpeed;
    }

    if (GetAsyncKeyState('A'))
    {
        root->rotation.y -= spinSpeed;
    }
    else if (GetAsyncKeyState('D'))
    {
        root->rotation.y += spinSpeed;
    }

}

void Robot::CreateParts()
{
    face = new Quad(sizeFace.x, sizeFace.y);
    face->GetMaterial()->SetDiffuseMap(L"Textures/Etc/face.jpg");

    parts.resize(Part::END);
    for (int i = 0; i < Part::END; i++)
    {
        parts[i] = new Cube(GetPartSize((Part)i));
        parts[i]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/white.jpg");
        parts[i]->GetMaterial()->SetShader(L"Shaders/Practice/RobotShader.hlsl");
    }
    parts[Part::BODY]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/body.jpg");
    parts[Part::LEFT_UPPER_ARM]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/body.jpg");
    parts[Part::RIGHT_UPPER_ARM]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/body.jpg");
    parts[Part::LEFT_UPPER_LEG]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/pants.jpg");
    parts[Part::RIGHT_UPPER_LEG]->GetMaterial()->SetDiffuseMap(L"Textures/Etc/pants.jpg");

    /*
    * 부모 관계 설정
    */
    parts[Part::BODY]->SetParent(root); // 기본 중심 설정
    
    parts[Part::HEAD]->SetParent(parts[Part::BODY]);
    
    parts[Part::LEFT_UPPER_ARM]->SetParent(parts[Part::BODY]);
    parts[Part::RIGHT_UPPER_ARM]->SetParent(parts[Part::BODY]);
    parts[Part::LEFT_UPPER_LEG]->SetParent(parts[Part::BODY]);
    parts[Part::RIGHT_UPPER_LEG]->SetParent(parts[Part::BODY]);

    parts[Part::LEFT_LOWER_ARM]->SetParent(parts[Part::LEFT_UPPER_ARM]);
    parts[Part::RIGHT_LOWER_ARM]->SetParent(parts[Part::RIGHT_UPPER_ARM]);
    parts[Part::LEFT_LOWER_LEG]->SetParent(parts[Part::LEFT_UPPER_LEG]);
    parts[Part::RIGHT_LOWER_LEG]->SetParent(parts[Part::RIGHT_UPPER_LEG]);

    face->SetParent(parts[Part::HEAD]);
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
    parts[Part::LEFT_UPPER_ARM]->SetPivot(0.0f, sizeUpperArm.y * 0.3f, 0.0f);
    parts[Part::LEFT_LOWER_ARM]->SetPivot(0.0f, sizeLowerArm.y * 0.3f, 0.0f);
    parts[Part::RIGHT_UPPER_ARM]->SetPivot(0.0f, sizeUpperArm.y * 0.3f, 0.0f);
    parts[Part::RIGHT_LOWER_ARM]->SetPivot(0.0f, sizeLowerArm.y * 0.3f, 0.0f);

    parts[Part::LEFT_UPPER_LEG]->SetPivot(0.0f, sizeUpperLeg.y * 0.4f, 0.0f);
    parts[Part::LEFT_LOWER_LEG]->SetPivot(0.0f, sizeLowerLeg.y * 0.4f, 0.0f);
    parts[Part::RIGHT_UPPER_LEG]->SetPivot(0.0f, sizeUpperLeg.y * 0.4f, 0.0f);
    parts[Part::RIGHT_LOWER_LEG]->SetPivot(0.0f, sizeLowerLeg.y * 0.4f, 0.0f);

    // Set Position
    parts[Part::HEAD]->position.y += (sizeBody.y * 0.5f + sizeHead.y * 0.5f);

    parts[Part::LEFT_UPPER_ARM]->position.x += (sizeBody.x * 0.5f + sizeUpperArm.x * 0.5f);
    parts[Part::LEFT_UPPER_ARM]->position.y += sizeBody.x * 0.2f;
    parts[Part::LEFT_LOWER_ARM]->position.y -= (sizeUpperArm.y * 0.5f + sizeLowerArm.y * 0.5f);

    parts[Part::RIGHT_UPPER_ARM]->position.x -= (sizeBody.x * 0.5f + sizeUpperArm.x * 0.5f);
    parts[Part::RIGHT_UPPER_ARM]->position.y += sizeBody.x * 0.2f;
    parts[Part::RIGHT_LOWER_ARM]->position.y -= (sizeUpperArm.y * 0.5f + sizeLowerArm.y * 0.5f);

    parts[Part::LEFT_UPPER_LEG]->position.x += sizeBody.x * 0.25f;
    parts[Part::LEFT_UPPER_LEG]->position.y -= (sizeBody.y * 0.5f + sizeUpperLeg.y * 0.5f);
    parts[Part::LEFT_LOWER_LEG]->position.y -= (sizeUpperLeg.y * 0.5f + sizeLowerLeg.y * 0.5f);

    parts[Part::RIGHT_UPPER_LEG]->position.x -= sizeBody.x * 0.25f;
    parts[Part::RIGHT_UPPER_LEG]->position.y -= (sizeBody.y * 0.5f + sizeUpperLeg.y * 0.5f);
    parts[Part::RIGHT_LOWER_LEG]->position.y -= (sizeUpperLeg.y * 0.5f + sizeLowerLeg.y * 0.5f);

    // 계산된 Position 기준으로 Body 위치 설정
    parts[Part::BODY]->position = root->position;
    parts[Part::BODY]->position.y = root->position.y + (-parts[Part::LEFT_UPPER_LEG]->position.y) + (-parts[Part::LEFT_LOWER_LEG]->position.y + sizeLowerLeg.y * 0.5f);

    face->position.z -= sizeHead.z * 0.51f;
}

void Robot::ShakeHand()
{
    static bool leftHandForward = true;
    static bool rightHandForward = false;

    float leftUpperArmRX = parts[Part::LEFT_UPPER_ARM]->rotation.x;
    float rightUpperArmRX = parts[Part::RIGHT_UPPER_ARM]->rotation.x;
    float leftLowerArmRX = parts[Part::LEFT_LOWER_ARM]->rotation.x;
    float rightLowerArmRX = parts[Part::RIGHT_LOWER_ARM]->rotation.x;

    if (leftHandForward)
    {
        parts[Part::LEFT_UPPER_ARM]->rotation.x += partRotationSpeed;
        parts[Part::LEFT_LOWER_ARM]->rotation.x += partRotationSpeed;
    }
    else
    {
        parts[Part::LEFT_UPPER_ARM]->rotation.x -= partRotationSpeed;

        if (leftLowerArmRX > 0)
            parts[Part::LEFT_LOWER_ARM]->rotation.x -= partRotationSpeed;
    }

    if (rightHandForward)
    {
        parts[Part::RIGHT_UPPER_ARM]->rotation.x += partRotationSpeed;
        parts[Part::RIGHT_LOWER_ARM]->rotation.x += partRotationSpeed;
    }
    else
    {
        parts[Part::RIGHT_UPPER_ARM]->rotation.x -= partRotationSpeed;

        if (rightLowerArmRX > 0)
            parts[Part::RIGHT_LOWER_ARM]->rotation.x -= partRotationSpeed;
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

    float leftUpperLegRX = parts[Part::LEFT_UPPER_LEG]->rotation.x;
    float rightUpperLegRX = parts[Part::RIGHT_UPPER_LEG]->rotation.x;
    float leftLowerLegRX = parts[Part::LEFT_LOWER_LEG]->rotation.x;
    float rightLowerLegRX = parts[Part::RIGHT_LOWER_LEG]->rotation.x;

    if (leftLegForward)
    {
        parts[Part::LEFT_UPPER_LEG]->rotation.x += partRotationSpeed;
        if (leftLowerLegRX > -1.2f)
            parts[Part::LEFT_LOWER_LEG]->rotation.x -= partRotationSpeed;
    }
    else
    {
        parts[Part::LEFT_UPPER_LEG]->rotation.x -= partRotationSpeed;
        if (leftLowerLegRX < 0)
            parts[Part::LEFT_LOWER_LEG]->rotation.x += partRotationSpeed * 1.5f;
    }

    if (rightLegForward)
    {
        parts[Part::RIGHT_UPPER_LEG]->rotation.x += partRotationSpeed;
        if (rightLowerLegRX > -1.2f)
            parts[Part::RIGHT_LOWER_LEG]->rotation.x -= partRotationSpeed;
    }
    else
    {
        parts[Part::RIGHT_UPPER_LEG]->rotation.x -= partRotationSpeed;
        if (rightLowerLegRX < 0)
            parts[Part::RIGHT_LOWER_LEG]->rotation.x += partRotationSpeed * 1.5f;
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
