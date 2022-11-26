#include "Framework.h"
#include "TerrainRobotScene.h"

TerrainRobotScene::TerrainRobotScene()
{
    viewBuffer = new MatrixBuffer();

    terrain = new Terrain();
    terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    robot = new Robot();
}

TerrainRobotScene::~TerrainRobotScene()
{
    delete robot;
    delete terrain;
}

void TerrainRobotScene::Update()
{
    robot->SetHeight(terrain->GetHeight(robot->GetPosition()));
    robot->Update();

    if (targetCamera)
        TargetCamera();
}

void TerrainRobotScene::Render()
{
    robot->Render();
    terrain->Render();
}

void TerrainRobotScene::GUIRender()
{
    ImGui::Checkbox("TargetCamera", &targetCamera);
}

void TerrainRobotScene::TargetCamera()
{
    Vector3 robotPos = robot->GetPosition();

    Vector4 eye = XMVectorSet(robotPos.x - 20.0f, robotPos.y + 20.0f, robotPos.z - 20.0f, 0);
    Vector4 focus = XMVectorSet(robotPos.x, robotPos.y + 10.0f, robotPos.z, 0);
    Vector4 up = XMVectorSet(0, 1, 0, 0);

    Matrix view = XMMatrixLookAtLH(eye, focus, up);
    viewBuffer->Set(view);
    viewBuffer->SetVSBuffer(1);
}
