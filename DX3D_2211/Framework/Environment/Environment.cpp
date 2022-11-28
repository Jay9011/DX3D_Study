#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateProjection();
    SetViewport();
	CreateStates();

	lightBuffer = new LightBuffer();
	mainCamera = new Camera();
}

Environment::~Environment()
{
	delete mainCamera;
    delete projectionBuffer;
	delete lightBuffer;
}

void Environment::Set()
{
	mainCamera->SetViewBuffer();
	lightBuffer->SetPSBuffer(0);
}

void Environment::GUIRender()
{
	string fps = "FPS : " + to_string((int)ImGui::GetIO().Framerate);
	ImGui::TextColored(ImVec4(0, 1, 0, 1), fps.c_str());

	mainCamera->GUIRender();
	
	ImGui::SliderFloat3("LightDir", (float*)&lightBuffer->GetLightDir(), -1, 1);
	ImGui::DragFloat("Shininess", &lightBuffer->GetShininess(), 0.1f, 1.0f);
}

void Environment::CreateProjection()
{
	projectionBuffer = new MatrixBuffer();

	Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);
	projectionBuffer->Set(projection);
	projectionBuffer->SetVSBuffer(2);
}

void Environment::SetViewport()
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = WIN_WIDTH;
	viewport.Height = WIN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewport);
}

void Environment::CreateStates()
{
	samplerState = new SamplerState();
	samplerState->PSSetState(0);
}
