#pragma once
#include "Screen.h"
#include "DXElements.h"

class Bitmap
{
private:
	IWICBitmapDecoder* imageDecoder;
	IWICBitmapFrameDecode* imageFrame;
	IWICFormatConverter* formatConverter;
	ID2D1Bitmap* dxbitmap;

public:
	IWICBitmap* wicbitmap;
	std::wstring file;
	int	x;
	int y;

	Bitmap(){}
	Bitmap(UINT width, UINT height);
	Bitmap(std::wstring file);
	void Draw(FLOAT rotation = 0.0F, FLOAT transparency = 1.0F);
	void Draw(int width, int height, FLOAT rotation = 0.0F, FLOAT transparency = 1.0F);
	void CopyTo(Bitmap* dest, int x, int y);
	void CopyTo(Bitmap* dest, int x, int y, int srcwidth, int srcheight, int srcx, int srcy);
	D2D1_SIZE_U GetSize();
	void SetSize(D2D1_SIZE_U size);
	void Rotate(double degrees);
	~Bitmap();
};

