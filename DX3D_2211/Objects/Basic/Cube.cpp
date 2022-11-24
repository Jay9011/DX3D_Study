#include "Framework.h"
#include "Cube.h"

Cube::Cube(Vector3 size) :
	size(size)
{
	material = new Material(L"Shaders/Texture.hlsl");

	CreateMesh();

	worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
	delete material;
	delete mesh;
	delete worldBuffer;
}

void Cube::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	mesh->IASet();
	material->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Cube::CreateMesh()
{
	Vector3 halfSize = size * 0.5f;

	vertices.resize(8);

	vertices[0].pos = { -halfSize.x, +halfSize.y, -halfSize.z };
	vertices[1].pos = { +halfSize.x, +halfSize.y, -halfSize.z };
	vertices[2].pos = { -halfSize.x, -halfSize.y, -halfSize.z };
	vertices[3].pos = { +halfSize.x, -halfSize.y, -halfSize.z };

	vertices[4].pos = { -halfSize.x, +halfSize.y, +halfSize.z };
	vertices[5].pos = { +halfSize.x, +halfSize.y, +halfSize.z };
	vertices[6].pos = { -halfSize.x, -halfSize.y, +halfSize.z };
	vertices[7].pos = { +halfSize.x, -halfSize.y, +halfSize.z };

	vertices[0].uv = { 0, 0 };
	vertices[1].uv = { 1, 0 };
	vertices[2].uv = { 0, 1 };
	vertices[3].uv = { 1, 1 };

	vertices[4].uv = { 1, 1 };
	vertices[5].uv = { 0, 1 };
	vertices[6].uv = { 1, 0 };
	vertices[7].uv = { 0, 0 };

	indices = {
		0, 1, 2, 2, 1, 3,	// Front
		0, 4, 5, 0, 5, 1,	// Top
		3, 1, 5, 3, 5, 7,	// Right
		5, 4, 7, 7, 4, 6,	// Back
		4, 0, 6, 6, 0, 2,	// Left
		2, 3, 6, 6, 3, 7	// Bottom
	};

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
