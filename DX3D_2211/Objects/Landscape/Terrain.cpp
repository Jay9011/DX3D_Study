#include "Framework.h"

Terrain::Terrain()
{
	material = new Material(L"Shaders/Texture.hlsl");

	CreateMesh();

	worldBuffer = new MatrixBuffer();

	heightMap = Texture::Add(L"Textures/HeightMaps/HeightMap.png");
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

void Terrain::CreateMesh()
{
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
			indices[count++] = (width * z + x);			// 0
			indices[count++] = (width * (z + 1) + x);	// 1
			indices[count++] = (width * z + x + 1);		// 2

			indices[count++] = (width * z + x + 1);		// 2
			indices[count++] = (width * (z + 1) + x);	// 1
			indices[count++] = (width * (z + 1) + x + 1);// 3
		}
	}

	mesh = new Mesh(vertices.data(), sizeof(VertexType), vertices.size(), indices.data(), indices.size());
}
