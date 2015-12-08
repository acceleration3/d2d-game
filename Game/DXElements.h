#pragma once
#include "stdafx.h"

class DXElements
{
public:
	static ID2D1Factory* factory;
	static IDWriteFactory* writeFactory;
	static IWICImagingFactory* imageFactory;
	static ID2D1HwndRenderTarget* renderTarget;
	static IDirectSound* dsound;
	static HWND hWnd;
};
	