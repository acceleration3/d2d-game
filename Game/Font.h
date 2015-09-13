#include "Screen.h"

class Font
{

private:
	pDXELEMENTS _dxelements;
	IDWriteTextFormat* _pTextFormat;
	D2D1_COLOR_F color;
	FLOAT size;
	FLOAT ConvertPointSizeToDIP(FLOAT points);

public:
	Font(wchar_t* fontName, FLOAT size, pDXELEMENTS dxelements, DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE style = DWRITE_FONT_STYLE_NORMAL);
	void DrawString(int x, int y, wchar_t* string, D2D1_COLOR_F color);
	~Font();
};

