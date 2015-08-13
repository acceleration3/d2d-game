#include "GameWindow.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
		PostQuitMessage(0);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GameWindow::GameWindow(int height, int width)
{
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.lpszClassName = L"GameRenderWindow";
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = GetModuleHandle(NULL);

	wprintf(L"Created and registered window class: %s.\n", wndClass.lpszClassName);

	RegisterClassEx(&wndClass);

	RECT renderRect = { 0, 0, width, height };

	AdjustWindowRectEx(&renderRect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	hWnd = CreateWindow(L"GameRenderWindow", L"Game", WS_VISIBLE | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, renderRect.right - renderRect.left, renderRect.bottom - renderRect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

	if (hWnd == NULL)
	{
		printf("Error creating the game window.\n");
		return;
	}
	else
		printf("Created the render window.\n", wndClass.lpszClassName);

	ShowWindow(hWnd, SW_SHOW);
}

bool GameWindow::InitDirectX()
{

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);

	if (res != S_OK)
	{
		printf("Failed to create a ID2D1Factory.\n");
		return false;
	}
	else
		printf("Successfully created a ID2D1Factory.\n");

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	res = factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientRect.right, clientRect.bottom)), &renderTarget);

	if (res != S_OK || renderTarget == NULL)
	{
		printf("Failed to create a RenderTarget for the render window.\n");
		return false;
	}
	else
		printf("Successfully created a RenderTarget for the render window.\n");

	renderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
	
	return true;
}

void GameWindow::GameLoop()
{
	MSG message;
	ZeroMemory(&message, sizeof(MSG));

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
			DispatchMessage(&message);
		else
		{
			renderTarget->BeginDraw();
			renderTarget->Clear(D2D1::ColorF(CLEAR_COLOR));

			//UPDATE

			//DRAW

			renderTarget->EndDraw();
		}
	}
}


GameWindow::~GameWindow()
{
	renderTarget->Clear();
	renderTarget->Release();
	factory->Release();
}
