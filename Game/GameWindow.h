#pragma once

#include "GameEvent.h"
#include <Windows.h>
#include <stdio.h>
#include "ScreenManager.h"


class GameWindow
{
	
private:

	HWND hWnd;
	DXELEMENTS dxelements;
	Graphics* graphics;
	WNDCLASSEX wndClass;
	const D2D1::ColorF CLEAR_COLOR = D2D1::ColorF::Black;

public:
	
	static const wchar_t* title;
	GameWindow(int height, int width);
	bool InitDirectX();
	void GameLoop();
	void Release();
	~GameWindow();
};

