#pragma once

#include "enet\enet.h"

namespace GameEvent
{
	enum EVENT_TYPE
	{ 
		MOUSE_GAMEEVENT,
		KEYDN_GAMEEVENT,
		KEYTP_GAMEEVENT,
		NETWK_GAMEEVENT
	};

	enum MOUSEBUTTON
	{
		LEFT,
		MIDDLE,
		RIGHT
	};

	class Event
	{
		public:
			EVENT_TYPE type;
	};

	class SocketEvent : public Event
	{
	public:
		SocketEvent(ENetEvent evt)
		{ 
			type = EVENT_TYPE::NETWK_GAMEEVENT;
			_evt = evt;
		}
		ENetEvent _evt;
	};

	class MouseEvent : public Event
	{
		
	public:
		MouseEvent(MOUSEBUTTON button, bool pressed, int x, int y)
		{ 
			type = EVENT_TYPE::MOUSE_GAMEEVENT; 
			_button = button;
			_pressed = pressed;
			_x = x;
			_y = y;
		}

		MOUSEBUTTON _button;
		bool _pressed;
		int _x;
		int _y;
	};

	class KeyTypedEvent : public Event
	{
	public:

		KeyTypedEvent(char key)
		{
			type = EVENT_TYPE::KEYTP_GAMEEVENT;
			_key = key;
		}
		char _key;
	};

	class KeyDownEvent : public Event
	{
	public:

	KeyDownEvent(char key, bool pressed)
	{
		type = EVENT_TYPE::KEYDN_GAMEEVENT;
		_key = key;
		_pressed = pressed;
	}
	char _key;
	bool _pressed;
};
}


