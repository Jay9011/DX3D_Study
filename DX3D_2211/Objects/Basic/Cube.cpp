#include "Framework.h"
#include "Cube.h"

Cube::Cube(Vector3 size) :
	size(size),
	scale(Vector3(1.0f, 1.0f, 1.0f)),
	rotationSpeed(0.0001f),
	translation(Vector3(0.0f, 0.0f, 0.0f))
{
	material = new Material(L"Shaders/Texture.hlsl");
	material->SetDiffuseMap(L"Textures/Landscape/Box.png");

	CreateMesh();

	worldBuffer = new MatrixBuffer();
}

Cube::~Cube()
{
	delete material;
	delete mesh;
	delete worldBuffer;
}

void Cube::Update()
{
	angle += rotationSpeed;

	/*
	* world SRT
	*/
	world = XMMatrixScaling(scale.x, scale.y, scale.z);
	world *= XMMatrixRotationX(angle) * XMMatrixRotationY(angle);
	world *= XMMatrixTranslation(translation.x, translation.y, translation.z);
	worldBuffer->Set(world);
}

void Cube::Render()
{
	worldBuffer->SetVSBuffer(0);

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
	Float3 halfSize = { size.x * 0.5f, size.y * 0.5f, size.z * 0.5f };

	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0, 0); // 0 : F LB
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 1, 0); // 1 : F RB
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 1); // 2 : F RT
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 1); // 3 : F LT
	
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 0, 0); // 4 : R LB
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 0); // 5 : R RB
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 1, 1); // 6 : R RT
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 0, 1); // 7 : R LT
	
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 0, 0); // 8  : B LB
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 1, 0); // 9  : B RB
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 1, 1); // 10 : B RT
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 0, 1); // 11 : B LT
	
	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0, 0); // 12 : L LB
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 1, 0); // 13 : L RB
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 1, 1); // 14 : L RT
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 1); // 15 : L LT
	
	vertices.emplace_back(-halfSize.x, +halfSize.y, -halfSize.z, 0, 0); // 16 : T LB
	vertices.emplace_back(+halfSize.x, +halfSize.y, -halfSize.z, 1, 0); // 17 : T RB
	vertices.emplace_back(+halfSize.x, +halfSize.y, +halfSize.z, 1, 1); // 18 : T RT
	vertices.emplace_back(-halfSize.x, +halfSize.y, +halfSize.z, 0, 1); // 19 : T LT

	vertices.emplace_back(-halfSize.x, -halfSize.y, +halfSize.z, 0, 0); // 20 : BT LB
	vertices.emplace_back(+halfSize.x, -halfSize.y, +halfSize.z, 1, 0); // 21 : BT RB
	vertices.emplace_back(+halfSize.x, -halfSize.y, -halfSize.z, 1, 1); // 22 : BT RT
	vertices.emplace_back(-halfSize.x, -halfSize.y, -halfSize.z, 0, 1); // 23 : BT LT

	indices = {
		0, 3, 2, 2, 1, 0,		// Front
		4, 7, 6, 6, 5, 4,		// Right
		8, 11, 10, 10, 9, 8,	// Back
		12, 15, 14, 14, 13, 12,	// Left
		16, 19, 18, 18, 17, 16, // Top
		20, 23, 22, 22, 21, 20	// Bottom
	};

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
