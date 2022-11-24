#include "Framework.h"
#include "Cube.h"

Cube::Cube(Vector3 size) :
	size(size),
	scale(Vector3(1.0f, 1.0f, 1.0f)),
	rotationSpeed(0.001f),
	translation(Vector3(0.0f, 0.0f, 0.0f))
{
	material = new Material(L"Shaders/Texture.hlsl");
	material->SetDiffuseMap(L"Textures/Landscape/Box.png");

	CreateMesh();

	//worldBuffer = new MatrixBuffer();

	//worldMatrix._11 = 1;
	//worldMatrix._22 = 1;
	//worldMatrix._33 = 1;
	//worldMatrix._44 = 1;
}

Cube::~Cube()
{
	delete material;
	delete mesh;
	//delete worldBuffer;
}
//
//void Cube::Update()
//{
//	static float angle = 0.0f;
//
//	if (GetAsyncKeyState('A'))
//		angle += rotationSpeed;
//	if (GetAsyncKeyState('D'))
//		angle -= rotationSpeed;
//
//	worldMatrix._11 = cos(angle);
//	worldMatrix._13 = -sin(angle);
//	worldMatrix._31 = sin(angle);
//	worldMatrix._33 = cos(angle);
//
//	world = XMLoadFloat4x4(&worldMatrix);
//}

void Cube::Render()
{
	/*worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);*/

	mesh->IASet();
	material->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

void Cube::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void Cube::SetRotateSpeed(float speed)
{
	this->rotationSpeed = speed;
}

void Cube::SetPos(Vector3 pos)
{
	this->translation = pos;
}

void Cube::CreateMesh()
{
	Vector3 halfSize = { size.x * 0.5f, size.y * 0.5f, size.z * 0.5f };

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

	vertices[4].uv = { 0, 0 };
	vertices[5].uv = { 1, 0 };
	vertices[6].uv = { 0, 1 };
	vertices[7].uv = { 1, 1 };

	indices = {
		0, 1, 2, 2, 1, 3,	// Front
		0, 4, 5, 0, 5, 1,	// Top
		3, 1, 5, 3, 5, 7,	// Right
	};

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
