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
	IWICBitmap* wicbitmap;

public:
	wstring file;
	int	x = 0;
	int y = 0;

	Bitmap(UINT width, UINT height, pDXELEMENTS dxelements);
	Bitmap(wstring file, pDXELEMENTS dxelements);
	void Draw(FLOAT transparency = 1.0F);
	void CopyTo(Bitmap* dest, int x, int y);
	~Bitmap();
};

