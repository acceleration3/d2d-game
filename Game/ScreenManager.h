#pragma once

#include "GameEvent.h"
#include <vector>
#include <Windows.h>
#include "Screen.h"
#include "Bitmap.h"
#include "Font.h"
#include "GameWindow.h"


class ScreenManager
{

private:
	
	static Screen* activeScreen;
	static std::vector<Screen*> screenList;
	static int frames;
	static int fps;
	static long lastFpsTick;
	static pDXELEMENTS _dxelements;

public:

	static void Initialize(pDXELEMENTS dxelements);
	static void OnDraw();
	static void OnUpdate();
	static void OnEvent(GameEvent::Event* evt);
	static void AddScreen(Screen* screen);
	static void SetActiveScreen(std::string name);

};

