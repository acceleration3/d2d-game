#include "stdafx.h"
#include "Button.h"

Button::Button(std::wstring text, std::string name) : text(text) 
{
	this->name = name;
	label = new Label(text);
	SetPosition(0, 0);
}

void Button::SetPosition(int x, int y)
{
	UIControl::SetPosition(x, y);
	label->x = x + 10;
	label->y = y;
	this->bounds.top = y;
	this->bounds.left = x;
	this->bounds.right = label->x + label->GetWidth() + 10;
	this->bounds.bottom = label->y + 22 + 10;
}



void Button::OnDraw()
{
	label->OnDraw();
}

void Button::OnEvent(GameEvent::Event* evt)
{
	switch (evt->type)
	{
		case GameEvent::EVENT_TYPE::GEVENT_MOUSEMOVE:
		{
			GameEvent::MouseMoveEvent moveEvt = *(GameEvent::MouseMoveEvent*)evt;

			if (moveEvt.x >= this->bounds.left && moveEvt.x <= this->bounds.right && moveEvt.y >= this->bounds.top && moveEvt.y <= this->bounds.bottom)
				label->SetColor(255, 11, 11);
			else
				label->SetColor(93, 93, 93);
		}

		case GameEvent::EVENT_TYPE::GEVENT_MOUSECLICK:
		{
			GameEvent::MouseClickEvent clickEvt = *(GameEvent::MouseClickEvent*)evt;

			if (clickEvt.button == GameEvent::MOUSEBUTTON::LEFT
				&& clickEvt.pressed == true
				&& clickEvt.x >= this->bounds.left
				&& clickEvt.x <= this->bounds.right
				&& clickEvt.y >= this->bounds.top
				&& clickEvt.y <= this->bounds.bottom)
				ScreenManager::OnEvent(new GameEvent::GUIEvent(this->name, "Click"));
		}

	}
}

Button::~Button()
{
	label = NULL;
}
