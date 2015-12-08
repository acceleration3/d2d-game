#include "stdafx.h"
#include "Message.h"

Panel* Message::panel = NULL;
Label* Message::text = NULL;
std::vector<std::wstring> Message::messages;
bool Message::visible = false;
UINT64 Message::lastTick = 0;
int Message::msgPos = 0;
bool Message::waitForKey = false;
int Message::msgDelay = MESSAGE_SPEED::MED;

void Message::Create()
{
	panel = new Panel((GameWindow::_width / Panel::TILE_SIZE) - 1, 8);
	panel->SetPosition(Panel::TILE_SIZE / 2, GameWindow::_height - panel->getHeight() - (Panel::TILE_SIZE / 2));

	text = new Label(L"", 32);
	text->SetPosition(panel->x + 20, panel->y + 18);
}

void Message::AddMessage(std::wstring message)
{
	messages.push_back(message);
}

void Message::OnDraw()
{
	if (visible)
	{
		panel->OnDraw();
		text->OnDraw();
	}
	
}

void Message::OnUpdate()
{
	if (messages.size() > 0)
	{
		if (!visible) 
			visible = true;

		if (lastTick == 0) 
			lastTick = GetTickCount64();

		if (!waitForKey)
		{
			if (GetTickCount64() >= lastTick + msgDelay)
			{
				text->text += messages[0][msgPos];

				if (text->GetWidth() > panel->getWidth() - 40)
				{
					text->text.pop_back();
					text->text += L"\r\n";
					text->text += messages[0][msgPos];
				}

				if (msgPos == messages[0].size() - 1)
					waitForKey = true;
				else
					msgPos++;
				lastTick = GetTickCount64();
			}
		}	
	}
	
}

void Message::OnEvent(GameEvent::Event* evt)
{
	if (waitForKey)
	{
		if (evt->type == GameEvent::EVENT_TYPE::GEVENT_KEYDOWN)
		{
			GameEvent::KeyDownEvent keyEvt = *(GameEvent::KeyDownEvent*)evt;

			if (keyEvt.key == 'Z' && keyEvt.pressed == true)
			{
				messages.erase(messages.begin());
				text->text = L"";
				msgPos = 0;
				waitForKey = false;
			}
		}
		
		if (evt->type == GameEvent::EVENT_TYPE::GEVENT_MOUSECLICK)
		{
			GameEvent::MouseClickEvent clickEvt = *(GameEvent::MouseClickEvent*)evt;

			if (clickEvt.button == GameEvent::MOUSEBUTTON::LEFT && clickEvt.pressed == true)
			{
				messages.erase(messages.begin());
				text->text = L"";
				msgPos = 0;
				waitForKey = false;
			}

		}

		if (messages.size() == 0)
			visible = false;
	}
}

void Message::SetSpeed(MESSAGE_SPEED speed)
{
	msgDelay = speed;
}

void Message::Destroy()
{
	messages.clear();
	delete panel;
}