#pragma once
#include <d3d9.h>
#include <d3dx9.h>

// 宏脚本
#define ARGB(a, r, g, b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

namespace I3DLib
{
	// 全局变量
	static IDirect3DDevice9* pDevice = 0;
	static IDirect3DSurface9* pSurface = 0;

	// 函数
	bool Init3DLib(HINSTANCE hInstance, HWND hWnd, int width, int height);
	int DrawPixel(int x, int y, DWORD color);
	void FlipSurface();
	void Release3DLib();
}

