#pragma once

#include <string>
#include <d2d1.h>
#include <dwrite.h>

#include "Graphics.h"

class Screen
{
	
public:

	std::string name;
	Screen(std::string name) : name(name){}
	
	virtual void LoadResources() = 0;
	virtual void OnDraw(Graphics* graphics) = 0;
	virtual void OnUpdate() = 0;
	virtual void OnKeyDown(int Key) = 0;
	virtual void OnKeyUp(int Key) = 0;
	virtual void OnMouseDown(int Button) = 0;
	virtual void OnMouseUp(int Button) = 0;
	virtual void OnEnter() = 0;
	virtual void OnLeave() = 0;

};

