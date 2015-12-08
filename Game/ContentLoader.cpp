#include "stdafx.h"
#include "ContentLoader.h"

std::vector<Bitmap*> ContentLoader::bitmaps;
std::wstring ContentLoader::bitmapFolder;
std::wstring ContentLoader::gameFolder;

void ContentLoader::LoadContent(std::wstring filename, Bitmap*& bitmap)
{
	filename = ContentLoader::bitmapFolder + filename;

	for (int i = 0; i < bitmaps.size(); i++)
	{
		if (bitmaps[i]->file == filename)	
		{ 
			bitmap = bitmaps[i];
			return;
		}
	}

	Bitmap* newbitmap = new Bitmap(filename);
	bitmap = newbitmap;
	bitmaps.push_back(newbitmap);
}