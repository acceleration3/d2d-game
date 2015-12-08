#pragma once
#include "UIControl.h"
#include "Font.h"

class Label : public UIControl
{
private:
	Font* font;
	int MakeInt(BYTE r, BYTE g, BYTE b);

	BYTE r;
	BYTE g;
	BYTE b;

public:
	std::wstring text;
	Label(std::wstring text, int size = 22, BYTE r = 99, BYTE g = 99, BYTE b = 107);

	void SetColor(BYTE r, BYTE g, BYTE b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	};
	
	void SetPosition(int x, int y)
	{
		UIControl::SetPosition(x, y);
	};
	
	int GetWidth()
	{
		return font->MeasureString(text);
	}

	void OnDraw() override;
	void OnUpdate(){}
	void OnEvent(GameEvent::Event* evt){};
	void OnGainFocus(){}
	void OnLoseFocus(){}
	~Label();
};

