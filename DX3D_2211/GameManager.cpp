#include "Framework.h"

#include "Scenes/TutorialScene.h"
#include "Scenes/CubeScene.h"
#include "Scenes/TerrainScene.h"
#include "Scenes/SphereScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/ShootingScene.h"

#include "Scenes/PracticeScene/TerrainRobotScene.h"
#include "Scenes/PracticeScene/FirstPersonShooterScene.h"

GameManager::GameManager()
{
	Create();

	//scene = new TutorialScene();
	//scene = new CubeScene();
	//scene = new TerrainScene();
	//scene = new SphereScene();
	//scene = new CollisionScene();
	scene = new ShootingScene();

	//scene = new TerrainRobotScene();
	//scene = new FirstPersonShooterScene();
}

GameManager::~GameManager()
{
	delete scene;

	Delete();
}

void GameManager::Update()
{
	scene->Update();

	Environment::Get()->GetMainCamera()->Update();
}

void GameManager::Render()
{
	Device::Get()->Clear();

	Environment::Get()->Set();
	scene->Render();

	Environment::Get()->PostSet();
	scene->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool isActive = true;

	if (isActive)
	{
		ImGui::Begin("Inspector", &isActive);
		Environment::Get()->GUIRender();
		scene->GUIRender();
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Device::Get();
	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Delete()
{
	Device::Delete();
	Shader::Delete();
	Texture::Delete();
	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
