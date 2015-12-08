#pragma once
#include "Screen.h"
#include "Bitmap.h"
#include "Font.h"
#include "GameWindow.h"
#include "LoginScreen.h"
#include "GameEvent.h"

class ScreenManager
{

private:
	
	static Screen* activeScreen;
	static std::vector<Screen*> screenList;
	static int frames;
	static int fps;
	static UINT64 lastFpsTick;


public:

	static void Initialize();
	static void OnDraw();
	static void OnUpdate();
	static void OnEvent(GameEvent::Event* evt);
	static void AddScreen(Screen* screen);
	static void SetActiveScreen(std::string name);

};

