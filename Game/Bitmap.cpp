#include "Bitmap.h"

Bitmap::Bitmap(UINT width, UINT height, pDXELEMENTS dxelements) : _dxelements(dxelements)
{
	dxelements->imageFactory->CreateBitmap(width, height, GUID_WICPixelFormat32bppPBGRA, WICBitmapCreateCacheOption::WICBitmapCacheOnLoad, &wicbitmap);
	dxelements->renderTarget->CreateBitmapFromWicBitmap(wicbitmap, NULL, &dxbitmap);
}

Bitmap::Bitmap(wstring file, pDXELEMENTS dxelements) : _dxelements(dxelements), file(file)
{
	HRESULT hr = _dxelements->imageFactory->CreateDecoderFromFilename(file.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &imageDecoder);

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

	hr = _dxelements->imageFactory->CreateFormatConverter(&formatConverter);

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

	_dxelements->renderTarget->CreateBitmapFromWicBitmap(formatConverter, NULL, &dxbitmap);
}


void Bitmap::Draw(FLOAT transparency)
{
	if (!dxbitmap)
		return;

	D2D1_SIZE_F size = dxbitmap->GetSize();
	_dxelements->renderTarget->DrawBitmap(dxbitmap, D2D1::RectF(x, y, x + size.width, y + size.height), transparency, D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1::RectF(0, 0, size.width, size.height));
}

void Bitmap::CopyTo(Bitmap* dest, int x, int y)
{
	D2D1_POINT_2U* destPt = new D2D1_POINT_2U(D2D1::Point2U(x, y));
	dest->dxbitmap->CopyFromBitmap(destPt, dxbitmap, new D2D1_RECT_U(D2D1::RectU(0, 0, dxbitmap->GetSize().width, dxbitmap->GetSize().height)));
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
	_dxelements = NULL;
}
