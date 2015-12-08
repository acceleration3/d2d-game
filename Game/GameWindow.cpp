#include "stdafx.h"
#include "GameWindow.h"

const wchar_t* GameWindow::title = L"GAME";
bool GameWindow::isFullscreen = false;
HWND GameWindow::hWnd = 0;
int GameWindow::_height = 0;
int GameWindow::_width = 0;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//KEYBOARD MESSAGES
		case WM_KEYDOWN:		
			ScreenManager::OnEvent(new GameEvent::KeyDownEvent((char)wParam, true));
			break;
		case WM_KEYUP:
			ScreenManager::OnEvent(new GameEvent::KeyDownEvent((char)wParam, false));
			break;
		case WM_CHAR:
			ScreenManager::OnEvent(new GameEvent::KeyTypedEvent((char)wParam));
			break;

		//MOUSE MESSAGES
		case WM_LBUTTONDOWN:
			ScreenManager::OnEvent(new GameEvent::MouseClickEvent(GameEvent::MOUSEBUTTON::LEFT, true, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_LBUTTONUP:
			ScreenManager::OnEvent(new GameEvent::MouseClickEvent(GameEvent::MOUSEBUTTON::LEFT, false, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_RBUTTONDOWN:
			ScreenManager::OnEvent(new GameEvent::MouseClickEvent(GameEvent::MOUSEBUTTON::RIGHT, true, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_RBUTTONUP:
			ScreenManager::OnEvent(new GameEvent::MouseClickEvent(GameEvent::MOUSEBUTTON::RIGHT, false, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_MBUTTONDOWN:
			ScreenManager::OnEvent(new GameEvent::MouseClickEvent(GameEvent::MOUSEBUTTON::MIDDLE, true, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_MBUTTONUP:
			ScreenManager::OnEvent(new GameEvent::MouseClickEvent(GameEvent::MOUSEBUTTON::MIDDLE, false, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_MOUSEMOVE:
			ScreenManager::OnEvent(new GameEvent::MouseMoveEvent(LOWORD(lParam), HIWORD(lParam)));
			break;

		//QUIT MESSAGE
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}	

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GameWindow::GameWindow(int height, int width)
{
	_height = height;
	_width = width;

	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	wndClass.cbSize = sizeof(WNDCLASSEX);
	//wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpszClassName = L"GameRenderWindow";
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = GetModuleHandle(NULL);

	wprintf(L"Created and registered window class: %s.\n", wndClass.lpszClassName);

	RegisterClassEx(&wndClass);

	RECT renderRect = { 0, 0, width, height };
	hWnd = CreateWindowW(L"GameRenderWindow", title, WS_VISIBLE | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, renderRect.right - renderRect.left, renderRect.bottom - renderRect.top, NULL, NULL, GetModuleHandle(NULL), NULL);
	DXElements::hWnd = hWnd;

	AdjustWindowRectEx(&renderRect, GetWindowLong(hWnd, GWL_STYLE), false, GetWindowLong(hWnd, GWL_EXSTYLE));
	SetWindowPos(hWnd, 0, 0, 0, renderRect.right - renderRect.left, renderRect.bottom - renderRect.top, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	if (hWnd == NULL)
	{
		printf("Error creating the game window.\n");
		return;
	}
	else
		printf("Created the render window.\n", wndClass.lpszClassName);

	RECT rc;

	GetWindowRect(hWnd, &rc);

	int xPos = (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2;

	SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	printf("Centered on screen. X=%d Y=%d.\n", xPos, yPos);

	ShowWindow(hWnd, SW_SHOW);
}

bool GameWindow::InitDirectX()
{

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &DXElements::factory);

	if (res != S_OK)
	{
		printf("Failed to create an ID2D1Factory interface.\n");
		return false;
	}
	else
		printf("Successfully created an ID2D1Factory interface.\n");


	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&DXElements::writeFactory);

	if (res != S_OK)
	{
		printf("Failed to create an IDWriteFactory interface.\n");
		return false;
	}
	else
		printf("Successfully created an IDWriteFactory interface.\n");

	res = DirectSoundCreate(NULL, &DXElements::dsound, NULL);

	if (res != S_OK)
	{
		printf("Failed to create an IDirectSound interface.\n");
		return false;
	}
	else
		printf("Successfully created an IDirectSound interface.\n");

	DXElements::dsound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);

	
	res = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&DXElements::imageFactory);
	
	if (res != S_OK)
	{
		printf("Failed to create a WICImagingFactory interface.\n");
		return false;
	}
	else
		printf("Successfully created a WICImagingFactory interface.\n");

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	D2D1_RENDER_TARGET_PROPERTIES renderProperties = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_HARDWARE, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 0, 0, D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT);

	res = DXElements::factory->CreateHwndRenderTarget(renderProperties, D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientRect.right, clientRect.bottom), D2D1_PRESENT_OPTIONS_NONE), &DXElements::renderTarget);
	
	if (res != S_OK || DXElements::renderTarget == NULL)
	{
		printf("Failed to create a RenderTarget for the render window.\n");
		return false;
	}
	else
		printf("Successfully created a RenderTarget for the render window.\n");

	DXElements::renderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
	
	return true;
}

void GameWindow::ToggleFullscreen()
{
	if (!isFullscreen)
	{
		
		LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_SYSMENU);
		SetWindowLong(hWnd, GWL_STYLE, lStyle);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0);
		RECT renderRect = { 0, 0, _width, _height };
		//DXElements::renderTarget->Resize(D2D1::SizeU(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)));
		isFullscreen = true;
	}
	else
	{
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX);
		RECT renderRect = { 0, 0, _width, _height };
		AdjustWindowRectEx(&renderRect, GetWindowLong(hWnd, GWL_STYLE), false, GetWindowLong(hWnd, GWL_EXSTYLE));
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, renderRect.right - renderRect.left, renderRect.bottom - renderRect.top, SWP_NOMOVE | SWP_NOACTIVATE);

		RECT rc;
		GetWindowRect(hWnd, &rc);
		int xPos = (GetSystemMetrics(SM_CXSCREEN) - (rc.right - rc.left)) / 2;
		int yPos = (GetSystemMetrics(SM_CYSCREEN) - (rc.bottom - rc.top)) / 2;

		SetWindowPos(hWnd, 0, xPos, yPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//DXElements::renderTarget->Resize(D2D1::SizeU(_width, _height));

		isFullscreen = false;
	}
	
}

void GameWindow::GameLoop()
{
	MSG message;

	ZeroMemory(&message, sizeof(MSG));

	ScreenManager::Initialize();

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			DXElements::renderTarget->BeginDraw();
			DXElements::renderTarget->Clear(D2D1::ColorF(CLEAR_COLOR));

			ScreenManager::OnUpdate();
			ScreenManager::OnDraw();

			DXElements::renderTarget->EndDraw();
		}
	}
}

void GameWindow::Release()
{
	delete this;
}

GameWindow::~GameWindow()
{
	if (DXElements::renderTarget) DXElements::renderTarget->Release();
	if (DXElements::factory) DXElements::factory->Release();
	if (DXElements::writeFactory) DXElements::writeFactory->Release();
	if (DXElements::imageFactory) DXElements::imageFactory->Release();
	if (DXElements::dsound) DXElements::dsound->Release();

	DXElements::factory = NULL;
	DXElements::renderTarget = NULL;
	DXElements::writeFactory = NULL;
	DXElements::imageFactory = NULL;
	DXElements::dsound = NULL;
	
	UnregisterClassW(L"GameRenderWindow", GetModuleHandle(NULL));
	DestroyWindow(hWnd);
}
