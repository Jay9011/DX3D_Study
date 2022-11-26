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

	vertices.resize(24);

	// Front
	vertices[0].pos = { -halfSize.x, -halfSize.y, -halfSize.z };
	vertices[1].pos = { +halfSize.x, -halfSize.y, -halfSize.z };
	vertices[2].pos = { -halfSize.x, +halfSize.y, -halfSize.z };
	vertices[3].pos = { +halfSize.x, +halfSize.y, -halfSize.z };
	// Right
	vertices[4].pos = { +halfSize.x, -halfSize.y, -halfSize.z };
	vertices[5].pos = { +halfSize.x, -halfSize.y, +halfSize.z };
	vertices[6].pos = { +halfSize.x, +halfSize.y, -halfSize.z };
	vertices[7].pos = { +halfSize.x, +halfSize.y, +halfSize.z };
	// Back
	vertices[8].pos =  { +halfSize.x, -halfSize.y, +halfSize.z };
	vertices[9].pos =  { -halfSize.x, -halfSize.y, +halfSize.z };
	vertices[10].pos = { +halfSize.x, +halfSize.y, +halfSize.z };
	vertices[11].pos = { -halfSize.x, +halfSize.y, +halfSize.z };
	//Left
	vertices[12].pos = { -halfSize.x, -halfSize.y, +halfSize.z };
	vertices[13].pos = { -halfSize.x, -halfSize.y, -halfSize.z };
	vertices[14].pos = { -halfSize.x, +halfSize.y, +halfSize.z };
	vertices[15].pos = { -halfSize.x, +halfSize.y, -halfSize.z };
	//Top
	vertices[16].pos = { -halfSize.x, +halfSize.y, -halfSize.z };
	vertices[17].pos = { +halfSize.x, +halfSize.y, -halfSize.z };
	vertices[18].pos = { -halfSize.x, +halfSize.y, +halfSize.z };
	vertices[19].pos = { +halfSize.x, +halfSize.y, +halfSize.z };
	//Bottom
	vertices[20].pos = { -halfSize.x, -halfSize.y, +halfSize.z };
	vertices[21].pos = { +halfSize.x, -halfSize.y, +halfSize.z };
	vertices[22].pos = { -halfSize.x, -halfSize.y, -halfSize.z };
	vertices[23].pos = { +halfSize.x, -halfSize.y, -halfSize.z };

	for (UINT i = 0; i < vertices.size() / 4; i++)
	{
		vertices[i * 4 + 0].uv = { 0, 1 };
		vertices[i * 4 + 1].uv = { 1, 1 };
		vertices[i * 4 + 2].uv = { 0, 0 };
		vertices[i * 4 + 3].uv = { 1, 0 };
	}

	indices.resize(36);
	UINT count = 0;

	for (UINT i = 0; i < vertices.size() / 4; i++)
	{
		indices[count++] = i * 4; // 0
		indices[count++] = i * 4 + 2; // 2
		indices[count++] = i * 4 + 1; // 1

		indices[count++] = i * 4 + 1; // 1
		indices[count++] = i * 4 + 2; // 2
		indices[count++] = i * 4 + 3; // 3
	}

	CreateNormal();

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}

void Cube::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v0 = vertices[index0].pos;
		Vector3 v1 = vertices[index1].pos;
		Vector3 v2 = vertices[index2].pos;

		Vector3 AVector = v1 - v0;
		Vector3 BVector = v2 - v1;

		Vector3 normal = Vector3::Cross(AVector, BVector).Normalized();

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}
}
