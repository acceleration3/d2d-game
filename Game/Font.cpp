#include "Font.h"


Font::Font(wchar_t* fontName, FLOAT size, pDXELEMENTS dxelements, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style)
{
	HRESULT hr = dxelements->writeFactory->CreateTextFormat(fontName, NULL, weight, style, DWRITE_FONT_STRETCH_NORMAL, ConvertPointSizeToDIP(size), L"en-us", &_pTextFormat);
	
	if (hr != S_OK)
	{ 
		wprintf(L"Unable to create text format for font: '%s' (%dpt).\n", fontName, (int)size);
		return;
	}

	this->_dxelements = dxelements;
	this->size = size;
}

void Font::DrawString(int x, int y, wchar_t* string, D2D1_COLOR_F color)
{
	ID2D1SolidColorBrush* brush = NULL;
	int length = wcslen(string);

	D2D1_RECT_F rect = D2D1::RectF((float)x, (float)y-3, (float)x + this->size * length, (float)y + this->size);

	this->_dxelements->renderTarget->CreateSolidColorBrush(color, &brush);
	this->_dxelements->renderTarget->DrawText(string, length, this->_pTextFormat, rect, brush);
	
	brush = NULL;
}

FLOAT Font::ConvertPointSizeToDIP(FLOAT points)
{
	return (points / 72.0f)*96.0f;
}

Font::~Font()
{
	if (_pTextFormat != NULL) _pTextFormat->Release();
	_pTextFormat = NULL;
	_dxelements = NULL;
}
