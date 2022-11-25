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

//ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#pragma comment(lib, "Libraries/ImGui/imGui.lib")

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
#include "Framework/Utility/BinaryReader.h"
#include "Framework/Utility/BinaryWriter.h"

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

#include "Framework/State/BlendState.h" // Alpha
#include "Framework/State/DepthStencilState.h"
#include "Framework/State/RasterizerState.h"    // 폴리곤의 완성시 시계방향과 반시계방향 혹은 양면 방향을 결정해준다.
#include "Framework/State/SamplerState.h"

#include "Framework/Environment/Environment.h"

#include "Framework/Math/Vector3.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

using namespace GameMath;

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"

//Object Header
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Cube.h"
#include "Objects/Custom/Robot.h"
#include "Objects/Landscape/Terrain.h"

//Scene Header
#include "Scenes/Scene.h"
#include "GameManager.h"

extern HWND hWnd;
