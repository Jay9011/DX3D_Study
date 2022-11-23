#include "Framework.h"
#include "Cube.h"

Cube::Cube() :
    Cube({ 0, 0, 0 })
{
}

Cube::Cube(Vector3 size)
{
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

	/*
	* world SRT
	*/
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

void Cube::CreateMesh()
{
	vertices.emplace_back(-1.0f, -1.0f, -1.0f, 1, 0, 0);
	vertices.emplace_back(+1.0f, -1.0f, -1.0f, 0, 1, 0);
	vertices.emplace_back(+1.0f, +1.0f, -1.0f, 0, 0, 1);
	vertices.emplace_back(-1.0f, +1.0f, -1.0f, 1, 1, 0);

	vertices.emplace_back(-1.0f, -1.0f, +1.0f, 1, 0, 0);
	vertices.emplace_back(+1.0f, -1.0f, +1.0f, 0, 1, 0);
	vertices.emplace_back(+1.0f, +1.0f, +1.0f, 0, 0, 1);
	vertices.emplace_back(-1.0f, +1.0f, +1.0f, 1, 1, 0);

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
