#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <Libraries/DirectXTex/DirectXTex.h>

#pragma comment(lib, "Libraries/DirectXTex/DirectXTex.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT2 Float2;
typedef XMFLOAT3 Float3;
typedef XMFLOAT4 Float4;
typedef XMVECTOR Vector4;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;

//Framework Header
#include "Framework/Utility/Singleton.h"
#include "Framework/Utility/Utility.h"

using namespace Utility;

#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayout.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Environment/Environment.h"

#include "Framework/Math/Vector3.h"
#include "Framework/Math/GameMath.h"

using namespace GameMath;

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"

//Object Header
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Cube.h"

//Scene Header
#include "Scenes/Scene.h"
#include "GameManager.h"

extern HWND hWnd;
