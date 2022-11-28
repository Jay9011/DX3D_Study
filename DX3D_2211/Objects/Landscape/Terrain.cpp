#include "Framework.h"

Terrain::Terrain()
{
	//material = new Material(L"Shaders/Terrain.hlsl");
	material = new Material(L"Shaders/Specular.hlsl");
	material->SetDiffuseMap(L"Textures/Landscape/Fieldstone_DM.tga");
	material->SetSpecularMap(L"Textures/Landscape/Fieldstone_SM.tga");

	heightMap = Texture::Add(L"Textures/HeightMaps/HeightMap.png");

	CreateMesh();

	worldBuffer = new MatrixBuffer();
}

Terrain::~Terrain()
{
	delete material;
	delete mesh;
	delete worldBuffer;
}

void Terrain::Render()
{
	worldBuffer->Set(world);
	worldBuffer->SetVSBuffer(0);

	mesh->IASet();
	material->Set();

	DC->DrawIndexed(indices.size(), 0, 0);
}

float Terrain::GetHeight(Vector3 position)
{
	int x = (int)position.x;
	int z = (int)position.z;

	if (x < 0 || x >= width - 1) return 0.0f;
	if (z < 0 || z >= height - 1) return 0.0f;

	UINT index[4];
	index[0] = width * z + x;
	index[1] = width * (z + 1) + x;
	index[2] = width * z + x + 1;
	index[3] = width * (z + 1) + x + 1;

	Vector3 p[4];
	for (UINT i = 0; i < 4; i++)
	{
		p[i] = vertices[index[i]].pos;
	}

	float u = position.x - p[0].x;
	float v = position.z - p[0].z;

	Vector3 result;
	
	if (u + v <= 1.0f)
	{
		result = ((p[2] - p[0]) * u + (p[1] - p[0]) * v) + p[0];
	}
	else
	{
		u = 1.0f - u;
		v = 1.0f - v;

		result = ((p[1] - p[3]) * u + (p[2] - p[3]) * v) + p[3];
	}

	return result.y;
}

void Terrain::CreateMesh()
{
	width = heightMap->Width();
	height = heightMap->Height();

	vector<Float4> pixels = heightMap->ReadPixels();

	// Vertices
	vertices.resize(width * height);
	
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			VertexType vertex;
			vertex.pos = Float3(x, 0, z);
			vertex.uv.x = x / (float)(width - 1);
			vertex.uv.y = z / (float)(height - 1);

			UINT index = width * z + x;
			vertex.pos.y = pixels[index].x * MAX_HEIGHT;

			vertices[index] = vertex;
		}
	}

	// Indices
	indices.resize((height - 1) * (width - 1) * 6);
	UINT count = 0;

	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width - 1; x++)
		{
			indices[count++] = (width * z + x);				// 0
			indices[count++] = (width * (z + 1) + x);		// 10	(width가 10인 경우)
			indices[count++] = (width * z + x + 1);			// 1

			indices[count++] = (width * z + x + 1);			// 1
			indices[count++] = (width * (z + 1) + x);		// 10
			indices[count++] = (width * (z + 1) + x + 1);	// 11
		}
	}

	CreateNormal();

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}

void Terrain::CreateNormal()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v0 = vertices[index0].pos;
		Vector3 v1 = vertices[index1].pos;
		Vector3 v2 = vertices[index2].pos;

		Vector3 A = v1 - v0;
		Vector3 B = v2 - v0;

		Vector3 normal = Vector3::Cross(A, B).Normalized();

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}
}
