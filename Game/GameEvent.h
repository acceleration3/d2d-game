#pragma once
#include "enet\enet.h"

namespace GameEvent
{
	enum EVENT_TYPE
	{
		GEVENT_MOUSECLICK,
		GEVENT_MOUSEMOVE,
		GEVENT_KEYDOWN,
		GEVENT_KEYTYPED,
		GEVENT_NETWORK,
		GEVENT_GUI
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
		SocketEvent(ENetEvent _evt)
		{ 
			type = EVENT_TYPE::GEVENT_NETWORK;
			evt = _evt;
		}
		ENetEvent evt;
	};

	class MouseClickEvent : public Event
	{
		
	public:
		MouseClickEvent(MOUSEBUTTON _button, bool _pressed, int _x, int _y)
		{ 
			type = EVENT_TYPE::GEVENT_MOUSECLICK; 
			button = _button;
			pressed = _pressed;
			x = _x;
			y = _y;
		}

		MOUSEBUTTON button;
		bool pressed;
		int x;
		int y;
	};

	class GUIEvent : public Event
	{
	public:
		GUIEvent(std::string controlName, std::string eventName)
		{
			this->type = GEVENT_GUI;
			this->eventName = controlName + "_" + eventName;
		}

		std::string eventName;

	};

	class MouseMoveEvent : public Event
	{
		
	public:
		MouseMoveEvent(int _x, int _y)
		{
			type = EVENT_TYPE::GEVENT_MOUSEMOVE;
			x = _x;
			y = _y;
		}

		int x;
		int y;
	};

	class KeyTypedEvent : public Event
	{
	public:

		KeyTypedEvent(char _key)
		{
			type = EVENT_TYPE::GEVENT_KEYTYPED;
			key = _key;
		}
		char key;
	};

	class KeyDownEvent : public Event
	{
	public:

		KeyDownEvent(char _key, bool _pressed)
	{
		type = EVENT_TYPE::GEVENT_KEYDOWN;
		key = _key;
		pressed = _pressed;
	}
	char key;
	bool pressed;
};
}


