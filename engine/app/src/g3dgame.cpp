#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <cstdio>

#include "GameObject.h"
#include "World.h"
#pragma comment(lib, "galaxy3d.lib")

static const char g_title[] = "Galaxy3D Game";
static const int g_screen_w = 640;
static const int g_screen_h = 480;
HINSTANCE g_hinst;
HWND g_hwnd;

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, int width, int height);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto obj = Galaxy3D::GameObject::Create("obj");
	auto obj2 = Galaxy3D::GameObject::Create("obj2");
	auto obj3 = Galaxy3D::GameObject::Create("obj3");
	obj2.lock()->GetTransform().lock()->SetParent(obj.lock()->GetTransform());
	obj2.lock()->GetTransform().lock()->SetParent(obj3.lock()->GetTransform());

	AllocConsole();
	FILE* fstdout = 0;
	freopen_s(&fstdout, "CONOUT$", "w", stdout);

	if(FAILED(InitWindow(hInstance, nCmdShow, g_screen_w, g_screen_h)))
		return 0;

	// Main message loop
	MSG msg = {0};
	while(WM_QUIT != msg.message)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(1);

			Galaxy3D::World::Update();
		}
	}

	if(fstdout != 0)
	{
		fclose(fstdout);
	}

	return (int)msg.wParam;
}

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = g_title;
	wcex.hIconSm = 0;
	if(!RegisterClassEx(&wcex))
		return E_FAIL;

	// Create window
	g_hinst = hInstance;
	RECT rc = {0, 0, width, height};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hwnd = CreateWindow(g_title, g_title, WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL);
	if(!g_hwnd)
		return E_FAIL;

	ShowWindow(g_hwnd, nCmdShow);

	return S_OK;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message != 132 && message != 32 && message != 512)
	{
		message = message;
	}

	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}