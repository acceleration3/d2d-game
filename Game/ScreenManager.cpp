#include "ScreenManager.h"

int ScreenManager::fps = 0;
int ScreenManager::frames = 0;
long ScreenManager::lastFpsTick = GetTickCount();
Screen* ScreenManager::activeScreen = NULL;
std::vector<Screen*> ScreenManager::screenList;
pDXELEMENTS ScreenManager::_dxelements = NULL;

Font* fpsfont;

void ScreenManager::Initialize(pDXELEMENTS dxelements)
{
	_dxelements = dxelements;
	fpsfont = new Font(L"Arial", 10, dxelements);
}

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

void ScreenManager::OnUpdate()
{
	if (activeScreen)
		activeScreen->OnUpdate();
}

void ScreenManager::OnDraw()
{
	if (activeScreen)
		activeScreen->OnDraw();

	//Calculate FPS
	if (GetTickCount() >= lastFpsTick + 1000)
	{
		fps = frames;
		frames = 0;
		lastFpsTick = GetTickCount();
	}	

	frames++;

	wchar_t* szNewTitle = new wchar_t[256];
	wsprintf(szNewTitle, L"FPS: %i", fps);
	fpsfont->DrawString(5, 5, szNewTitle, D2D1::ColorF(D2D1::ColorF::Aquamarine));
	delete[] szNewTitle;

}

void ScreenManager::OnEvent(GameEvent::Event* evt)
{
	
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
