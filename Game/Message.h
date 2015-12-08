#pragma once

#include "GameWindow.h"
#include "GameEvent.h"
#include "Label.h"
#include "Panel.h"

class Message
{
private:
	static std::vector<std::wstring> messages;
	static Panel* panel;
	static Label* text;
	static int msgDelay;
	static UINT64 lastTick;
	static int msgPos;
	static bool waitForKey;

public:

	typedef enum
	{
		FAST = 16,
		MED = 20,
		SLOW = 40
	} MESSAGE_SPEED;

	static bool visible;
	static void OnEvent(GameEvent::Event* evt);
	static void AddMessage(std::wstring);
	static void OnDraw();
	static void SetSpeed(MESSAGE_SPEED speed);
	static void OnUpdate();
	static void Create();
	static void Destroy();
};

