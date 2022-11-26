#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateProjection();
    SetViewport();
	CreateStates();

	lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
    delete viewBuffer;
    delete projectionBuffer;
	delete lightBuffer;
}

void Environment::GUIRender()
{
	lightBuffer->SetVSBuffer(3);
	ImGui::SliderFloat3("LightDir", (float*)&lightBuffer->GetLightDir(), -1, 1);

	Matrix view = XMMatrixLookAtLH(eye, focus, up);
	viewBuffer->Set(view);
	viewBuffer->SetVSBuffer(1);
	ImGui::SliderFloat3("eye", (float*)&eye, 1, 256);
	ImGui::SliderFloat3("focus", (float*)&focus, 1, 256);
}

void Environment::CreateProjection()
{
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();

	Matrix view = XMMatrixLookAtLH(eye, focus, up);
	viewBuffer->Set(view);
	viewBuffer->SetVSBuffer(1);

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
