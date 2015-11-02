#include "ScreenManager.h"
#include "IntroScreen.h"

int ScreenManager::fps = 0;
int ScreenManager::frames = 0;
UINT64 ScreenManager::lastFpsTick = GetTickCount();
Screen* ScreenManager::activeScreen = NULL;
std::vector<Screen*> ScreenManager::screenList;
pDXELEMENTS ScreenManager::_dxelements = NULL;


Font* fpsfont;

void ScreenManager::Initialize(pDXELEMENTS dxelements)
{
	_dxelements = dxelements;
	fpsfont = new Font(L"Arial", 10, dxelements);
	AddScreen(new IntroScreen(dxelements));
	SetActiveScreen("introscreen");
}

void ScreenManager::AddScreen(Screen* screen)
{
	for (unsigned int i = 0; i < screenList.size(); i++)
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

	wstring newTitle(L"FPS: ");
	newTitle += std::to_wstring(fps);
	fpsfont->DrawString(5, 5, &newTitle[0], D2D1::ColorF(D2D1::ColorF::Aquamarine));

}

void ScreenManager::OnEvent(GameEvent::Event* evt)
{
	if (evt->type == GameEvent::EVENT_TYPE::GEVENT_KEYDOWN)
	{
		GameEvent::KeyDownEvent* keyEvt = (GameEvent::KeyDownEvent*)evt;
		if (keyEvt->key == VK_F1 && keyEvt->pressed == true)
			GameWindow::ToggleFullscreen();
			
	}

	if (activeScreen)
		activeScreen->OnEvent(evt);

	delete evt;
}

void ScreenManager::SetActiveScreen(std::string name)
{
	if (activeScreen)
		activeScreen->OnLeave();

	for (unsigned int i = 0; i < screenList.size(); i++)
		if (screenList[i]->name == name)
			activeScreen = screenList[i];

	if (activeScreen)
		activeScreen->OnEnter();
}
