#pragma once

#include <string>

#include "Screen.h"

using namespace std;

class Bitmap
{
private:
	pDXELEMENTS _dxelements;
	IWICBitmapDecoder* imageDecoder;
	IWICBitmapFrameDecode* imageFrame;
	IWICFormatConverter* formatConverter;
	ID2D1Bitmap* dxbitmap;

public:
	IWICBitmap* wicbitmap;
	wstring file;
	int	x;
	int y;

	Bitmap(UINT width, UINT height, pDXELEMENTS dxelements);
	Bitmap(wstring file, pDXELEMENTS dxelements);
	void Draw(FLOAT rotation = 0.0F, FLOAT transparency = 1.0F);
	void CopyTo(Bitmap* dest, int x, int y);
	D2D1_SIZE_U GetSize();
	void SetSize(D2D1_SIZE_U size);
	void Rotate(double degrees);
	~Bitmap();
};

