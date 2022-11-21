#pragma once // Test

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGTH 720

// Windows 헤더 파일
#include <windows.h>

// DirectX 11
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib");

// Framework Header
#include "Framework/Device/Device.h"

// Object Header

// Scene Header
#include "Scenes/Scene.h"