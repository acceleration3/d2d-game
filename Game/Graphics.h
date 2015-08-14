#pragma once

#include <d2d1.h>
#include <dwrite.h>

class Graphics
{
public:
	ID2D1HwndRenderTarget* renderTarget;
	IDWriteFactory* writeFactory;

	Graphics(ID2D1HwndRenderTarget* renderTarget, IDWriteFactory* writeFactory) : renderTarget(renderTarget), writeFactory(writeFactory){}

	void GDrawText(int x, int y, wchar_t* text, wchar_t* fontName, int fontSize, DWRITE_FONT_STYLE style, D2D1_COLOR_F color);
	void GDrawImage();

};

