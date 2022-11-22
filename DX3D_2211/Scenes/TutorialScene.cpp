#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = WIN_WIDTH;
	viewport.Height = WIN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	DC->RSSetViewports(1, &viewport);

	//vertexShader = Shader::AddVS(L"Shaders/Tutorial.hlsl");
	//pixelShader = Shader::AddPS(L"Shaders/Tutorial.hlsl");
		
	// 정점(Vertex) : 3D공간에서의 한 점
	// Polygon : 정점 3개로 이루어진 3차원 공간에서의 삼각형
	// 정점 순서에 따라서 시계방향이 앞면이며 앞면만 출력됨.
	//vertices.emplace_back(-0.5f, -0.5f, -0.5f, 1, 0, 0);
	//vertices.emplace_back(+0.5f, -0.5f, -0.5f, 0, 1, 0);
	//vertices.emplace_back(+0.5f, +0.5f, -0.5f, 0, 0, 1);
	//vertices.emplace_back(-0.5f, +0.5f, -0.5f, 1, 1, 0);

	//vertices.emplace_back(-0.5f, -0.5f, +0.5f, 1, 0, 0);
	//vertices.emplace_back(+0.5f, -0.5f, +0.5f, 0, 1, 0);
	//vertices.emplace_back(+0.5f, +0.5f, +0.5f, 0, 0, 1);
	//vertices.emplace_back(-0.5f, +0.5f, +0.5f, 1, 1, 0);
	//
	//vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

	//indices = { 0, 3, 2, 2, 1, 0 };

	//indexBuffer = new IndexBuffer(indices.data(), indices.size());

	cubes.push_back(new Cube());
	cubes.push_back(new Cube({-5.0f, 0.0f, 0.0f}, 0.3f));
	cubes.push_back(new Cube({1.5f, 0.0f, 10.0f}, 1.0f));

	//worldBuffer = new MatrixBuffer();
	viewBuffer = new MatrixBuffer();
	projectionBuffer = new MatrixBuffer();	

	Vector4 eye = XMVectorSet(3, 3, -5, 0);
	Vector4 focus = XMVectorSet(0, 0, 0, 0);
	Vector4 up = XMVectorSet(0, 1, 0, 0);

	Matrix view = XMMatrixLookAtLH(eye, focus, up);
	viewBuffer->Set(view);
	viewBuffer->SetVSBuffer(1);

	Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 1000.0f);
	projectionBuffer->Set(projection);
	projectionBuffer->SetVSBuffer(2);
}

TutorialScene::~TutorialScene()
{
	//delete vertexBuffer;
	//delete indexBuffer;

	//delete worldBuffer;
	delete viewBuffer;
	delete projectionBuffer;
}

void TutorialScene::Update()
{
	//static float angle = 0.0f;

	//angle += 0.001f;

	//world = XMMatrixRotationY(angle);
	//worldBuffer->Set(world);

	for (auto& cube : cubes)
	{
		cube->Update();
	}
}

void TutorialScene::Render()
{
	//worldBuffer->SetVSBuffer(0);

	//vertexBuffer->IASet(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//indexBuffer->IASet();

	//vertexShader->Set();
	//pixelShader->Set();

	//DC->DrawIndexed(indices.size(), 0, 0);
	for (auto& cube : cubes)
	{
		cube->Render();
	}
}

void TutorialScene::GUIRender()
{
}
