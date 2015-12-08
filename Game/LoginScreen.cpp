#include "stdafx.h"
#include "LoginScreen.h"

LoginScreen::LoginScreen() : Screen("loginscreen")
{
	index = 1;
}

void LoginScreen::OnEnter()
{
	Screen::OnEnter();

	md5 = new MD5();

	Message::Create();

	ContentLoader::LoadContent(L"bg.png", bg);
	bg->x = bg->y = 0;

	loginPanel = new Panel(14, 14);
	userLabel = new Label(L"Username:");
	userText = new TextBox(160, TextBox::ALPHALOWER + TextBox::ALPHAUPPER + TextBox::NUMERIC, 15);
	passLabel = new Label(L"Password:");
	passText = new TextBox(160, TextBox::ALPHALOWER + TextBox::ALPHAUPPER + TextBox::NUMERIC, 15, true);
	loginButton = new Button(L"Login", "loginButton");

	loginPanel->SetPosition((800 / 2) - (loginPanel->getWidth() / 2), 250);
	userLabel->SetPosition(loginPanel->x + 32, loginPanel->y + 32);
	userText->SetPosition(userLabel->x, userLabel->y + 30);
	passLabel->SetPosition(userLabel->x, userText->y + 40);
	passText->SetPosition(passLabel->x, passLabel->y + 30);
	loginButton->SetPosition((800 / 2) - (loginButton->getWidth() / 2), loginPanel->y + loginPanel->getHeight() - 55);

	controlgroup.AddControl(userText);
	controlgroup.AddControl(passText);
	controlgroup.AddControl(loginButton);
}



void LoginScreen::OnLeave()
{
	Screen::OnLeave();
	delete md5;
	delete bg;
}

void LoginScreen::OnDraw()
{
	bg->Draw();
	loginPanel->OnDraw();
	userLabel->OnDraw();
	passLabel->OnDraw();
	controlgroup.OnDraw();
	Message::OnDraw();
}

void LoginScreen::OnUpdate()
{
	Message::OnUpdate();
}

void LoginScreen::OnEvent(GameEvent::Event* evt)
{
	if (Message::visible)
		Message::OnEvent(evt);
	else
	{ 
		controlgroup.OnEvent(evt);

		if (evt->type == GameEvent::EVENT_TYPE::GEVENT_GUI)
		{
			GameEvent::GUIEvent guiEvent = *(GameEvent::GUIEvent*)evt;

			if (guiEvent.eventName == "loginButton_Click")
			{
				if (userText->text.length() > 6 && passText->text.length() > 6)
				{
					std::wstringstream oss;
					std::string str(passText->text.begin(), passText->text.end());
					std::string hash = md5->digestString(&str[0]);
					Message::AddMessage(L"Username: " + userText->text + L", hashed password: " + std::wstring(hash.begin(), hash.end()) + L".");
				}
				else
				{
					Message::AddMessage(L"Both the username and password need to be greater than 6 characters in length.");
				}
			}
		}
	}
	
}

LoginScreen::~LoginScreen()
{

}