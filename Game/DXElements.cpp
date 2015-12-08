#include "stdafx.h"
#include "DXElements.h"

ID2D1Factory* DXElements::factory = NULL;
IDWriteFactory* DXElements::writeFactory = NULL;
IWICImagingFactory* DXElements::imageFactory = NULL;
ID2D1HwndRenderTarget* DXElements::renderTarget = NULL;
IDirectSound* DXElements::dsound = NULL;
HWND DXElements::hWnd = NULL;