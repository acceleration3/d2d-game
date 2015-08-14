#pragma once

#include <Windows.h>
#include <stdio.h>
#include <d2d1.h>
#include <dwrite.h>

#include "ScreenManager.h"
#include "Graphics.h"


class GameWindow
{
	
private:

	HWND hWnd;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1Factory* factory;
	IDWriteFactory* writeFactory;
	Graphics* graphics;
	WNDCLASSEX wndClass;
	const D2D1::ColorF CLEAR_COLOR = D2D1::ColorF::CornflowerBlue;

public:

	GameWindow(int height, int width);
	bool InitDirectX();
	void GameLoop();
	~GameWindow();

};

