#pragma once

#include "enet\enet.h"
#include "Screen.h"
#include "Button.h"
#include "TextBox.h"
#include "Panel.h"
#include "Message.h"
#include "Label.h"
#include "md5.h"
#include "GameEvent.h"
#include "ControlGroup.h"

class Button;

class LoginScreen : public Screen
{
private:
	ENetHost* host;
	Bitmap* bg;
	ControlGroup controlgroup;
	Panel* loginPanel;
	Label* userLabel;
	Label* passLabel;
	Button* loginButton;
	MD5* md5;
	TextBox* userText;
	TextBox* passText;
	int index;

public:

	LoginScreen();
	void OnEnter() override;
	void OnEvent(GameEvent::Event* evt) override;
	void OnUpdate() override;
	void OnDraw() override;
	void OnLeave() override;
	friend void loginButton_Click(Screen* screen);
	~LoginScreen();
};