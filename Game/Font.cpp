#include "stdafx.h"
#include "Font.h"


Font::Font(std::wstring fontName, FLOAT size, DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style)
{
	HRESULT hr = DXElements::writeFactory->CreateTextFormat(fontName.c_str(), NULL, weight, style, DWRITE_FONT_STRETCH_NORMAL, ConvertPointSizeToDIP(size), L"pt-pt", &_pTextFormat);

	if (hr != S_OK)
	{
		wprintf(L"Unable to create text format for font: '%s' (%dpt).\n", fontName.c_str(), (int)size);
		return;
	}

	this->size = size;
}

void Font::DrawString(int x, int y, std::wstring string, D2D1_COLOR_F color)
{
	ID2D1SolidColorBrush* brush = NULL;
	int length = string.length();

	D2D1_RECT_F rect = D2D1::RectF((float)x, (float)y - 3, (float)x + this->size * length * 2, (float)y + this->size);

	DXElements::renderTarget->CreateSolidColorBrush(color, &brush);
	DXElements::renderTarget->DrawText(string.c_str(), length, this->_pTextFormat, rect, brush);

	brush->Release();
}

int Font::MeasureString(std::wstring string)
{
	IDWriteTextLayout* layout;
	DWRITE_TEXT_METRICS metrics;
	int width = 0;
	
	DXElements::writeFactory->CreateTextLayout(string.c_str(), string.length(), _pTextFormat, 20000, 100, &layout);
	layout->GetMetrics(&metrics);
	width = metrics.width;
	return width;
}


FLOAT Font::ConvertPointSizeToDIP(FLOAT points)
{
	return (points / 72.0f)*96.0f;
}

Font::~Font()
{
	if (_pTextFormat != NULL) _pTextFormat->Release();
	_pTextFormat = NULL;
}