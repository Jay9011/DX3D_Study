#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/TerrainScene.h"

GameManager::GameManager()
{
	Create();

	//scene = new TutorialScene();
	//scene = new CubeScene();
	scene = new TerrainScene();
}

GameManager::~GameManager()
{
	delete scene;
}

void GameManager::Update()
{
	scene->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	scene->Render();
	scene->GUIRender();

	Device::Get()->Present();
}

void GameManager::Create()
{
	Device::Get();
	Environment::Get();
}

void GameManager::Delete()
{
	Device::Delete();
	Shader::Delete();
	Texture::Delete();
	Environment::Delete();
}
