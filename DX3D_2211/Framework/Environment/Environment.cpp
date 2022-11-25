#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
    CreateProjection();
    SetViewport();
	CreateStates();

	lightBuffer = new LightBuffer();
	lightBuffer->SetVSBuffer(3);
}

Environment::~Environment()
{
    delete viewBuffer;
    delete projectionBuffer;
	delete lightBuffer;
}

void Environment::CreateProjection()
{
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();

	Vector4 eye = XMVectorSet(128, 50, 0, 0);
	Vector4 focus = XMVectorSet(128, 0, 128, 0);
	Vector4 up = XMVectorSet(0, 1, 0, 0);

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
