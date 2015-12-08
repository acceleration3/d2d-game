#pragma once
#include "GameEvent.h"
#include "ScreenManager.h"
#include "DXElements.h"

class GameWindow
{
	
private:
	WNDCLASSEXW wndClass;
	const D2D1::ColorF CLEAR_COLOR = D2D1::ColorF::Black;
	static bool isFullscreen;
	ID2D1DCRenderTarget* screen;
	
public:
	static const wchar_t* title;
	static int _height;
	static int _width;
	static HWND hWnd;

	GameWindow(int height, int width);
	bool InitDirectX();
	void GameLoop();
	static void ToggleFullscreen();
	void Release();
	~GameWindow();
};

