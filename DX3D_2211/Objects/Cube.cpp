#include "Framework.h"
#include "Cube.h"

Cube::Cube() :
    Cube({ 0, 0, 0 })
{
}

Cube::Cube(Float3 pos) :
    Cube(pos, 0.5f)
{
}

Cube::Cube(Float3 pos, float size) :
	Cube(pos, size, 0.0001f)
{
}

Cube::Cube(Float3 pos, float size, float speed) :
	position(pos),
	rotationSpeed(speed)
{
	vertexShader = Shader::AddVS(L"Shaders/Tutorial.hlsl");
	pixelShader = Shader::AddPS(L"Shaders/Tutorial.hlsl");

	SetVertex(size);

	worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
	delete vertexBuffer;
	delete indexBuffer;

	delete worldBuffer;
}

void Cube::Update()
{
	angle += rotationSpeed;

	world = XMMatrixRotationX(angle) * XMMatrixRotationY(angle);
	world *= XMMatrixTranslation(position.x, position.y, position.z);

	worldBuffer->Set(world);
}

void Cube::Render()
{
	worldBuffer->SetVSBuffer(0);

	vertexBuffer->IASet(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	indexBuffer->IASet();

	vertexShader->Set();
	pixelShader->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Cube::SetVertex(float size)
{
	vertices.emplace_back(-size, -size, -size, 1, 0, 0);
	vertices.emplace_back(+size, -size, -size, 0, 1, 0);
	vertices.emplace_back(+size, +size, -size, 0, 0, 1);
	vertices.emplace_back(-size, +size, -size, 1, 1, 0);

	vertices.emplace_back(-size, -size, +size, 1, 0, 0);
	vertices.emplace_back(+size, -size, +size, 0, 1, 0);
	vertices.emplace_back(+size, +size, +size, 0, 0, 1);
	vertices.emplace_back(-size, +size, +size, 1, 1, 0);

	vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexColor), vertices.size());

	indices = {
		0, 3, 2, 2, 1, 0,
		1, 2, 6, 6, 5, 1,
		5, 6, 7, 7, 4, 5,
		4, 7, 3, 3, 0, 4,
		3, 7, 6, 6, 2, 3,
		0, 1, 5, 5, 4, 0
	};

	indexBuffer = new IndexBuffer(indices.data(), indices.size());
}
