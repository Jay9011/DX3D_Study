#include "Framework.h"
#include "CubeScene.h"

CubeScene::CubeScene()
{
    quad = new Quad();
}

CubeScene::~CubeScene()
{
    delete quad;
}

void CubeScene::Update()
{
}

void CubeScene::Render()
{
    quad->Render();
}

void CubeScene::GUIRender()
{
}
