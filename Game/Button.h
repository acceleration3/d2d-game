#pragma once

#include "UIControl.h"
#include "Label.h"
#include "ScreenManager.h"

class Button : public UIControl
{
public:

	std::wstring text;
	Label* label;
	Screen* screen;

	Button(std::wstring text, std::string name);

	int getWidth()
	{
		return bounds.right - bounds.left;
	}
	
	int getHeight()
	{
		return bounds.bottom - bounds.top;
	}

	void OnDraw() override;
	void SetPosition(int x, int y) override;
	void OnUpdate(){}
	void OnEvent(GameEvent::Event* evt) override;
	void OnGainFocus(){}
	void OnLoseFocus(){}
	~Button();
};

