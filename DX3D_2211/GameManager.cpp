#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/CubeScene.h"

GameManager::GameManager()
{
	Create();

	//scene = new TutorialScene();
	scene = new CubeScene();
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
	Environment::Delete();
}
