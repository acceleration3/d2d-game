#include "Graphics.h"

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

void Graphics::GDrawText(int x, int y, wchar_t* text, wchar_t* fontName, int fontSize, DWRITE_FONT_STYLE style, D2D1_COLOR_F color)
{
	ID2D1SolidColorBrush* brush;
	IDWriteTextFormat* textFormat;
	UINT32 textLength;
	
	textLength = (UINT32)wcslen(text);

	writeFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_REGULAR, style, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"en-us", &textFormat);
	textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
	renderTarget->DrawTextW(text, textLength, textFormat, D2D1::RectF(x, y, fontSize * textLength, y + fontSize), brush);

	SafeRelease(&brush);
	SafeRelease(&textFormat);
}
