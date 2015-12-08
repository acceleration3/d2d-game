#pragma once

#include "UIControl.h"
#include "GameEvent.h"

class ControlGroup
{
private:
	std::vector<UIControl*> controls;

public:
	ControlGroup();
	void AddControl(UIControl* control);
	void OnEvent(GameEvent::Event* evt);
	void OnDraw();
	void OnUpdate();
	~ControlGroup();
};

