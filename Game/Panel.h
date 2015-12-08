#pragma once
#include "UIControl.h"
#include "Bitmap.h"
#include "ContentLoader.h"

class Panel : public UIControl
{
private:
	int tileWidth;
	int tileHeight;

	static Bitmap* panel;

public:
	static int currentSkin;
	static const int TILE_SIZE = 16;

	Panel(int tileWidth, int tileHeight);

	int getWidth()
	{
		return tileWidth * TILE_SIZE;
	}

	int getHeight()
	{
		return tileHeight  * TILE_SIZE;
	}

	static void ChangeSkin(int index);
	void OnDraw() override;
	void SetPosition(int x, int y) override;
	void OnUpdate(){}
	void OnEvent(GameEvent::Event* evt){};
	void OnGainFocus(){}
	void OnLoseFocus(){}

	~Panel();
};

