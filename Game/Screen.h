#pragma once

#include <vld.h>
#include "GameEvent.h"
#include <string>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dsound.h>
#include "Graphics.h"

typedef struct
{
	ID2D1Factory* factory;
	IDWriteFactory* writeFactory;
	IWICImagingFactory* imageFactory;
	ID2D1HwndRenderTarget* renderTarget;
	IDirectSound* dsound;
} DXELEMENTS, *pDXELEMENTS;

class Screen
{

public:

	std::string name;
	pDXELEMENTS dxelements;

	Screen(std::string name, pDXELEMENTS dxelements) : name(name), dxelements(dxelements){}
	
	virtual void OnDraw() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEvent(GameEvent::Event* evt) = 0;
	virtual void OnEnter() = 0;
	virtual void OnLeave() = 0;

};

