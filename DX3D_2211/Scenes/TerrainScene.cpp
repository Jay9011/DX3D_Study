#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
    terrain = new Terrain();
    //terrain->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Dirt2.png");

    rasterizerState = new RasterizerState();
    //rasterizerState->FillMode(D3D11_FILL_WIREFRAME);
    rasterizerState->SetState();
}

TerrainScene::~TerrainScene()
{
    delete terrain;
}

void TerrainScene::Update()
{
}

void TerrainScene::Render()
{
    terrain->Render();
}

void TerrainScene::GUIRender()
{
}
