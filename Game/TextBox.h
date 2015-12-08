#pragma once
#include "Font.h"
#include "UIControl.h"
#include "DXElements.h"
#include "Bitmap.h"
#include "GameEvent.h"
#include "ContentLoader.h"

class TextBox : public UIControl
{
private:
	std::wstring allowedChars;

	Bitmap* textbox;
	Bitmap* sheet;
	Bitmap* sheet2;
	Bitmap* textboxfocus;
	Bitmap* focussheet;
	Font* textboxFont;

public:

	static const std::wstring ALPHALOWER;
	static const std::wstring ALPHAUPPER;
	static const std::wstring SPACE;
	static const std::wstring NUMERIC;

	int maxChars;
	int width;
	bool masked;

	std::wstring text;
	std::wstring mask;

	TextBox(int width, std::wstring allowedChars, int maxChars, bool masked = false);
	void OnDraw() override;
	void SetPosition(int x, int y) override;
	void OnUpdate(){}
	void OnEvent(GameEvent::Event* evt) override;
	void OnGainFocus(){}
	void OnLoseFocus(){}
	~TextBox();

};

