#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{
    quad = new Quad();
    cubes.push_back(new Cube({ 1.0f, 1.0f, 1.0f }));
    cubes.push_back(new Cube({ 1.0f, 1.0f, 1.0f }));
    cubes.push_back(new Cube({ 1.0f, 1.0f, 1.0f }));

    cubes[1]->SetPos({-3.0f, 0.0f, 0.0f});
    cubes[1]->SetRotateSpeed(0.00015f);
    cubes[1]->SetScale({ 0.3f, 0.3f, 0.3f });
    cubes[2]->SetPos({0.5f, -1.0f, 5.0f});
    cubes[2]->SetRotateSpeed(0.0002f);
    cubes[2]->SetScale({ 3.0f, 3.0f, 3.0f });
}

CubeScene::~CubeScene()
{
    delete quad;

    for (auto& cube : cubes)
        delete cube;

    cubes.clear();
}

void CubeScene::Update()
{
    for (auto& cube : cubes)
        cube->Update();
}

void CubeScene::Render()
{
    //quad->Render();

    for (auto& cube : cubes)
        cube->Render();
}

void CubeScene::GUIRender()
{
}
