/****************************/
//Author : Burnian
//Date : 2016/12/20
/****************************/

#include <Windows.h>
#include <WindowsX.h>

#include "I3DLib.h"
using namespace I3DLib;

// 宏定义
#define WINDOW_CLASS_NAME TEXT("I3DWNDCLS")
#define WINDOW_TITLE TEXT("I3DCONSOLE")
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32
#define WAIT_TIME 30

// 全局变量定义
HWND g_WindowHandle;
HINSTANCE g_HInstance;
DWORD g_Clock;

// 宏脚本
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

// 函数定义
DWORD GetClock()
{
	return GetTickCount();
}

void StartClock()
{
	g_Clock = GetClock();
}

void WaitClock()
{
	while ((GetClock() - g_Clock) < WAIT_TIME)
	{
		Sleep(5);
	}
}

int Game_Init()
{
	Init3DLib(g_HInstance, g_WindowHandle, SCREEN_WIDTH, SCREEN_HEIGHT);
	return 1;
}

int Game_Main()
{
	// 画图
// 	for (int x = 0; x < 50; ++x)
// 	{
// 		for (int y = 0; y < 50; ++y)
// 		{
// 			DrawPixel(x, y, ARGB(0, 255, 0, 255));
// 		}
// 	}

	return 1;
}

int Game_Shutdown()
{
	Release3DLib();
	return 1;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (msg)
	{
	case WM_CREATE:
	{
		return 0;
	} break;
	case WM_KEYDOWN:
	{
		if (wParam == VK_ESCAPE)
		{
			PostMessage(g_WindowHandle, WM_DESTROY, 0, 0);
		} break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	} break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	default:break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS winclass;
	HWND hwnd;
	MSG msg;

	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;

	if (!RegisterClass(&winclass))
	{
		return 0;
	}

	if (!(hwnd = CreateWindow(WINDOW_CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0, 0,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL)))
	{
		return 0;
	}

	g_HInstance = hInstance;
	g_WindowHandle = hwnd;

	if (!Game_Init())
	{
		return 0;
	}

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		StartClock();
		Game_Main();
		// 输出
		FlipSurface();
		WaitClock();
	}

	Game_Shutdown();

	return msg.wParam;
}