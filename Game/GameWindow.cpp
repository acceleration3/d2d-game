#include "GameWindow.h"

const wchar_t* GameWindow::title = L"GAME";

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//KEY MESSAGES
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
			ScreenManager::OnEvent(new GameEvent::MouseEvent(GameEvent::MOUSEBUTTON::LEFT, true, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_LBUTTONUP:
			ScreenManager::OnEvent(new GameEvent::MouseEvent(GameEvent::MOUSEBUTTON::LEFT, false, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_RBUTTONDOWN:
			ScreenManager::OnEvent(new GameEvent::MouseEvent(GameEvent::MOUSEBUTTON::RIGHT, true, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_RBUTTONUP:
			ScreenManager::OnEvent(new GameEvent::MouseEvent(GameEvent::MOUSEBUTTON::RIGHT, false, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_MBUTTONDOWN:
			ScreenManager::OnEvent(new GameEvent::MouseEvent(GameEvent::MOUSEBUTTON::MIDDLE, true, LOWORD(lParam), HIWORD(lParam)));
			break;
		case WM_MBUTTONUP:
			ScreenManager::OnEvent(new GameEvent::MouseEvent(GameEvent::MOUSEBUTTON::MIDDLE, false, LOWORD(lParam), HIWORD(lParam)));
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
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpszClassName = L"GameRenderWindow";
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hInstance = GetModuleHandle(NULL);

	wprintf(L"Created and registered window class: %s.\n", wndClass.lpszClassName);

	RegisterClassEx(&wndClass);

	RECT renderRect = { 0, 0, width, height };

	AdjustWindowRectEx(&renderRect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);
	hWnd = CreateWindow(L"GameRenderWindow", title, WS_VISIBLE | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, renderRect.right - renderRect.left, renderRect.bottom - renderRect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

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

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &dxelements.factory);

	if (res != S_OK)
	{
		printf("Failed to create an ID2D1Factory interface.\n");
		return false;
	}
	else
		printf("Successfully created an ID2D1Factory interface.\n");


	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&dxelements.writeFactory);

	if (res != S_OK)
	{
		printf("Failed to create an IDWriteFactory interface.\n");
		return false;
	}
	else
		printf("Successfully created an IDWriteFactory interface.\n");

	res = DirectSoundCreate(NULL, &dxelements.dsound, NULL);

	if (res != S_OK)
	{
		printf("Failed to create an IDirectSound interface.\n");
		return false;
	}
	else
		printf("Successfully created an IDirectSound interface.\n");

	dxelements.dsound->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);

	
	res = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&dxelements.imageFactory);
	
	if (res != S_OK)
	{
		printf("Failed to create a WICImagingFactory interface.\n");
		return false;
	}
	else
		printf("Successfully created a WICImagingFactory interface.\n");

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	D2D1_RENDER_TARGET_PROPERTIES renderProperties;

	renderProperties.dpiX = 0.0F;
	renderProperties.dpiY = 0.0F;
	renderProperties.minLevel = D2D1_FEATURE_LEVEL_9;						//Support for DirectX9
	renderProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;				//GPU Rendering
	renderProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
	renderProperties.usage = D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE;		//Allow GDI calls (Screenshots and screen recording)

	res = dxelements.factory->CreateHwndRenderTarget(renderProperties, D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientRect.right, clientRect.bottom)), &dxelements.renderTarget);

	if (res != S_OK || dxelements.renderTarget == NULL)
	{
		printf("Failed to create a RenderTarget for the render window.\n");
		return false;
	}
	else
		printf("Successfully created a RenderTarget for the render window.\n");

	dxelements.renderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
	
	return true;
}

void GameWindow::GameLoop()
{
	MSG message;
	ZeroMemory(&message, sizeof(MSG));

	ScreenManager::Initialize(&dxelements);

	while (message.message != WM_QUIT)
	{
		if (PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			dxelements.renderTarget->BeginDraw();
			dxelements.renderTarget->Clear(D2D1::ColorF(CLEAR_COLOR));

			ScreenManager::OnUpdate();
			ScreenManager::OnDraw();

			dxelements.renderTarget->EndDraw();
		}
	}
}

void GameWindow::Release()
{
	delete this;
}

GameWindow::~GameWindow()
{
	if (dxelements.renderTarget) dxelements.renderTarget->Release();
	if (dxelements.factory) dxelements.factory->Release();
	if (dxelements.writeFactory) dxelements.writeFactory->Release();
	if (dxelements.imageFactory) dxelements.imageFactory->Release();
	if (dxelements.dsound) dxelements.dsound->Release();

	dxelements.factory = NULL;
	dxelements.renderTarget = NULL;
	dxelements.writeFactory = NULL;
	dxelements.imageFactory = NULL;
	dxelements.dsound = NULL;
	
	UnregisterClass(L"GameRenderWindow", GetModuleHandle(NULL));
	DestroyWindow(hWnd);
}
