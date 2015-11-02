#pragma once
#include "Screen.h"

class IntroScreen : virtual public Screen
{
public:

	IntroScreen(pDXELEMENTS dxelements) : Screen("introscreen", dxelements)
	{
	}

	void IntroScreen::OnEnter()
	{

	}

	void IntroScreen::OnEvent(GameEvent::Event* evt)
	{

			
	}

	void IntroScreen::OnUpdate()
	{
		
	}

	void IntroScreen::OnDraw()
	{
		
	}

	void IntroScreen::OnLeave()
	{

	}

	~IntroScreen()
	{
		
	}
};

