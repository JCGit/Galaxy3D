#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <cstdio>

#include "World.h"
#include "GraphicsDevice.h"
#include "Screen.h"
#include "Camera.h"
#include "Sprite.h"
#include "Application.h"
#include "SpriteRenderer.h"
#include "Texture2D.h"

#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "png.lib")
#pragma comment(lib, "zlib.lib")
#pragma comment(lib, "galaxy3d.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace Galaxy3D;

static const char g_title[] = "Galaxy3D Game";
static const int g_screen_w = 960;
static const int g_screen_h = 640;
HINSTANCE g_hinst;
HWND g_hwnd;

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow, int width, int height);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AllocConsole();
	SetConsoleTitle("Galaxy3D Console");
	FILE* fstdout = 0;
	freopen_s(&fstdout, "CONOUT$", "w", stdout);

	if(FAILED(InitWindow(hInstance, nCmdShow, g_screen_w, g_screen_h)))
		return 0;

	Screen::SetSize(g_screen_w, g_screen_h);
	GraphicsDevice::GetInstance()->Init(g_hwnd);

	auto cam = GameObject::Create("camera")->AddComponent<Camera>();
	cam->SetOrthographicSize(g_screen_h/200.f);
	auto sprite = Sprite::Create(Application::GetDataPath() + "/Assets/texture/mustang.jpg");
	auto renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->SetSprite(sprite);

	auto tex = Texture2D::LoadImageFile(Application::GetDataPath() + "/Assets/texture/test.png");

	float h = 384.f;
	std::shared_ptr<Sprite> sps[20];
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<4; j++)
		{
			sps[i*4 + j] = Sprite::Create(tex, Rect(192.f*i, h*j, 192, h), Vector2(96, h), 100, Vector4());
		}
	}

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(-3, -2.f, 0));
	renderer->SetSprite(sps[0]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(-2, -2.f, 0));
	renderer->SetSprite(sps[1]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(-1, -2.f, 0));
	renderer->SetSprite(sps[2]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(0, -2.f, 0));
	renderer->SetSprite(sps[3]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(1, -2.f, 0));
	renderer->SetSprite(sps[4]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(2, -2.f, 0));
	renderer->SetSprite(sps[5]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(3, -2.f, 0));
	renderer->SetSprite(sps[6]);

	renderer = GameObject::Create("renderer")->AddComponent<SpriteRenderer>();
	renderer->GetTransform()->SetPosition(Vector3(4, -2.f, 0));
	renderer->SetSprite(sps[7]);

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

			World::Update();
			Camera::RenderAll();
		}
	}

	World::Destroy();

	if(fstdout != 0)
	{
		fclose(fstdout);
	}

	return (int) msg.wParam;
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
