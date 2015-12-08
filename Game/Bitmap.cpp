#include "stdafx.h"
#include "Bitmap.h"

Bitmap::Bitmap(UINT width, UINT height)
{
	DXElements::imageFactory->CreateBitmap(width, height, GUID_WICPixelFormat32bppPBGRA, WICBitmapCreateCacheOption::WICBitmapCacheOnLoad, &wicbitmap);
	DXElements::renderTarget->CreateBitmapFromWicBitmap(wicbitmap, NULL, &dxbitmap);
	this->formatConverter = NULL;
	this->imageDecoder = NULL;
	this->imageFrame = NULL;
}

Bitmap::Bitmap(std::wstring file) : file(file)
{
	wicbitmap = NULL;
	HRESULT hr = DXElements::imageFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &imageDecoder);

	if (hr != S_OK)
	{
		wprintf(L"Failed loading the image: %s %x.\n", file.c_str(), hr);
		return;
	}

	hr = imageDecoder->GetFrame(0, &imageFrame);

	if (hr != S_OK)
	{
		wprintf(L"Failed getting frame 0 for the image: %s.\n", file.c_str());
		return;
	}


	hr = DXElements::imageFactory->CreateFormatConverter(&formatConverter);

	if (hr != S_OK)
	{
		wprintf(L"Failed creating a format converter for the image: %s.\n", file.c_str());
		return;
	}


	hr = formatConverter->Initialize(imageFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeCustom);
	
	if (hr != S_OK)
	{
		wprintf(L"Failed initializing a format converter for the image: %s.\n", file.c_str());
		return;
	}

	DXElements::renderTarget->CreateBitmapFromWicBitmap(formatConverter, NULL, &dxbitmap);
}


void Bitmap::Draw(int width, int height, FLOAT rotation, FLOAT transparency)
{
	if (!dxbitmap)
		return;

	D2D1_SIZE_F size = dxbitmap->GetSize();

	D2D1::Matrix3x2F angle = D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(x + (size.width / 2), y + (size.height / 2)));
	DXElements::renderTarget->SetTransform(angle);
	DXElements::renderTarget->DrawBitmap(dxbitmap, D2D1::RectF(x, y, x + width, y + height), transparency, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0F, 0.0F, size.width, size.height));
	DXElements::renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Bitmap::Draw(FLOAT rotation, FLOAT transparency)
{
	if (!dxbitmap)
		return;

	D2D1_SIZE_F size = dxbitmap->GetSize();

	D2D1::Matrix3x2F angle = D2D1::Matrix3x2F::Rotation(rotation, D2D1::Point2F(x + (size.width / 2), y + (size.height / 2)));
	DXElements::renderTarget->SetTransform(angle);
	DXElements::renderTarget->DrawBitmap(dxbitmap, D2D1::RectF(x, y, x + size.width, y + size.height), transparency, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0.0F, 0.0F, size.width, size.height));
	DXElements::renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

D2D1_SIZE_U Bitmap::GetSize()
{
	return dxbitmap->GetPixelSize();
}

void Bitmap::CopyTo(Bitmap* dest, int x, int y)
{
	D2D1_POINT_2U* destPt = new D2D1_POINT_2U(D2D1::Point2U(x, y));
	D2D1_RECT_U srcRect = D2D1::RectU(0, 0, dxbitmap->GetSize().width, dxbitmap->GetSize().height);
	dest->dxbitmap->CopyFromBitmap(destPt, dxbitmap, &srcRect);
	delete destPt;
}

void Bitmap::CopyTo(Bitmap* dest, int destx, int desty, int srcwidth, int srcheight, int srcx, int srcy)
{
	D2D1_POINT_2U* destPt = new D2D1_POINT_2U(D2D1::Point2U(destx, desty));
	D2D1_RECT_U srcRect = D2D1::RectU(srcx, srcy, srcx + srcwidth, srcy + srcheight);
	dest->dxbitmap->CopyFromBitmap(destPt, dxbitmap, &srcRect);
	delete destPt;
}

Bitmap::~Bitmap()
{
	if (wicbitmap != NULL) wicbitmap->Release();
	if (dxbitmap != NULL) dxbitmap->Release();
	if (formatConverter != NULL) formatConverter->Release();
	if (imageFrame != NULL) imageFrame->Release();
	if (imageDecoder != NULL) imageDecoder->Release();
	dxbitmap = NULL;
	formatConverter = NULL;
	imageFrame = NULL;
	imageDecoder = NULL;
	wicbitmap = NULL;
}
