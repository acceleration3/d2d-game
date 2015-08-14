#include "ScreenManager.h"

int ScreenManager::fps = 0;
int ScreenManager::frames = 0;
long ScreenManager::lastFpsTick = GetTickCount();
Screen* ScreenManager::activeScreen = NULL;
std::vector<Screen*> ScreenManager::screenList;

void ScreenManager::AddScreen(Screen* screen)
{
	for (int i = 0; i < screenList.size(); i++)
		if (screenList[i]->name == screen->name)
		{
			printf("A screen with the same name ('%s') has already been added.\n", screen->name);
			return;
		}
	screenList.push_back(screen);
}

void ScreenManager::LoadResources()
{
	for (int i = 0; i < screenList.size(); i++)
		screenList[i]->LoadResources();
}

void ScreenManager::OnUpdate()
{
	if (activeScreen)
		activeScreen->OnUpdate();
}

void ScreenManager::OnDraw(Graphics* graphics)
{
	if (activeScreen)
		activeScreen->OnDraw(graphics);

	frames++;

	//Calculate FPS
	if (GetTickCount() >= lastFpsTick + 1000)
	{
		fps = frames;
		frames = 0;
		lastFpsTick = GetTickCount();
	}	

	wchar_t* szFPS = new wchar_t[256];
	wsprintf(szFPS, L"FPS: %i", fps);
	graphics->GDrawText(1, 1, szFPS, L"Arial", 12, DWRITE_FONT_STYLE_NORMAL, D2D1::ColorF(D2D1::ColorF::White));
	delete[] szFPS;
}

void ScreenManager::OnWindowMessage(UINT msg, LPARAM lParam, WPARAM wParam)
{
	//TODO: Process messages and send relevant ones to the active screen
}

void ScreenManager::SetActiveScreen(std::string name)
{
	if (activeScreen)
		activeScreen->OnLeave();

	for (int i = 0; i < screenList.size(); i++)
		if (screenList[i]->name == name)
			activeScreen = screenList[i];

	if (activeScreen)
		activeScreen->OnEnter();
}
