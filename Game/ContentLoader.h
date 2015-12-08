#pragma once
#include "Bitmap.h"

class ContentLoader
{

private:
	static std::vector<Bitmap*> bitmaps;
public:
	static std::wstring bitmapFolder;
	static std::wstring gameFolder;
	static void LoadContent(std::wstring filename, Bitmap*& bitmap);
};

