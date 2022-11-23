#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
	vertexShader = Shader::AddVS(L"Shaders/Tutorial.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/Tutorial.hlsl");
		
	// ����(Vertex) : 3D���������� �� ��
	// Polygon : ���� 3���� �̷���� 3���� ���������� �ﰢ��
	// ���� ������ ���� �ð������ �ո��̸� �ո鸸 ��µ�.
	vertices.emplace_back(-0.5f, -0.5f, -0.5f, 1, 0, 0);
	vertices.emplace_back(+0.5f, -0.5f, -0.5f, 0, 1, 0);
	vertices.emplace_back(+0.5f, +0.5f, -0.5f, 0, 0, 1);
	vertices.emplace_back(-0.5f, +0.5f, -0.5f, 1, 1, 0);

	vertices.emplace_back(-0.5f, -0.5f, +0.5f, 1, 0, 0);
	vertices.emplace_back(+0.5f, -0.5f, +0.5f, 0, 1, 0);
	vertices.emplace_back(+0.5f, +0.5f, +0.5f, 0, 0, 1);
	vertices.emplace_back(-0.5f, +0.5f, +0.5f, 1, 1, 0);
	
	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

	indices = { 0, 3, 2, 2, 1, 0 };

	indexBuffer = new IndexBuffer(indices.data(), indices.size());

	worldBuffer = new MatrixBuffer();
}

TutorialScene::~TutorialScene()
{
	delete vertexBuffer;
	delete indexBuffer;

	delete worldBuffer;
	delete viewBuffer;
	delete projectionBuffer;
}

void TutorialScene::Update()
{
	static float angle = 0.0f;

	angle += 0.001f;

	world = XMMatrixRotationY(angle);
	worldBuffer->Set(world);
}

void TutorialScene::Render()
{
	worldBuffer->SetVSBuffer(0);

	vertexBuffer->IASet(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	indexBuffer->IASet();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void TutorialScene::GUIRender()
{
}
