#pragma once


#include <vector>
#include <Windows.h>
#include "Screen.h"

class ScreenManager
{

private:
	
	static Screen* activeScreen;
	static std::vector<Screen*> screenList;
	static int frames;
	static int fps;
	static long lastFpsTick;

public:

	static void LoadResources();
	static void OnDraw(Graphics* graphics);
	static void OnUpdate();
	static void OnWindowMessage(UINT msg, LPARAM lParam, WPARAM wParam);
	static void AddScreen(Screen* screen);
	static void SetActiveScreen(std::string name);

};

