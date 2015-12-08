#pragma once
#include "DXElements.h"
#include "GameEvent.h"

class Screen
{

public:

	std::string name;

	Screen(std::string name) : name(name){}
	virtual void OnDraw() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnEvent(GameEvent::Event* evt) = 0;
	virtual void OnEnter()
	{
		printf_s("Entered %s.\n", name.c_str());
	}
	virtual void OnLeave()
	{
		printf_s("Left %s.\n", name.c_str());
	}

};

