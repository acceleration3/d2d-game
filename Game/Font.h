#pragma once
#include "DXElements.h"

class Font
{

private:
	IDWriteTextLayout* layout;
	IDWriteTextFormat* _pTextFormat;
	D2D1_COLOR_F color;
	FLOAT size;
	FLOAT ConvertPointSizeToDIP(FLOAT points);

public:
	Font(std::wstring fontName, FLOAT size, DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL);
	void DrawString(int x, int y, std::wstring string, D2D1_COLOR_F color);
	int MeasureString(std::wstring string);
	~Font();
};
