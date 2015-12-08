#pragma once
#include "Screen.h"
#include "DXElements.h"

class UIControl
{

public:
	
	typedef struct
	{
		int top;
		int left;
		int bottom;
		int right;
	} Bounds;

	Bounds bounds;
	
	std::string name;

	bool focused = false;

	int x;
	int y;

	UIControl()
	{
		this->x = 0;
		this->y = 0;
		this->focused = false;
	}

	virtual void SetPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	virtual void OnDraw() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEvent(GameEvent::Event* evt) = 0;
	virtual void OnGainFocus() = 0;
	virtual void OnLoseFocus() = 0;

};

