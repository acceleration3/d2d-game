#include "stdafx.h"
#include "TextBox.h"

const std::wstring TextBox::ALPHALOWER = std::wstring(L"abcdefghijklmnopqrstuvwxyz");
const std::wstring TextBox::ALPHAUPPER = std::wstring(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const std::wstring TextBox::SPACE = std::wstring(L" ");
const std::wstring TextBox::NUMERIC = std::wstring(L"0123456789");

TextBox::TextBox(int width, std::wstring allowedChars, int maxChars, bool masked) : UIControl(), width(width), allowedChars(allowedChars), maxChars(maxChars), masked(masked)
{
	if (width < 18) width = 18;

	textboxFont = new Font(L"Pokemon DPPt", 16);

	textbox = new Bitmap(width, 22);
	textboxfocus = new Bitmap(width, 22);

	ContentLoader::LoadContent(L"textbox.png", sheet);
	ContentLoader::LoadContent(L"textbox_focus.png", focussheet);

	sheet->CopyTo(textbox, 0, 0, 9, 22, 0, 0);
	focussheet->CopyTo(textboxfocus, 0, 0, 9, 22, 0, 0);

	for (int i = 0; i < width - 18; i++)
	{
		sheet->CopyTo(textbox, 9 + i, 0, 1, 22, 13, 0);
		focussheet->CopyTo(textboxfocus, 9 + i, 0, 1, 22, 13, 0);
	}

	sheet->CopyTo(textbox, width - 9, 0, 9, 22, 31, 0);
	focussheet->CopyTo(textboxfocus, width - 9, 0, 9, 22, 31, 0);
}

void TextBox::SetPosition(int x, int y)
{
	UIControl::SetPosition(x, y);
	textbox->x = x;
	textbox->y = y;
	textboxfocus->x = x;
	textboxfocus->y = y;

	bounds.top = y;
	bounds.left = x;
	bounds.right = x + width;
	bounds.bottom = y + 22;
}

void TextBox::OnEvent(GameEvent::Event* evt)
{
	if (!focused)
		return;

	switch (evt->type)
	{
		case GameEvent::GEVENT_KEYTYPED:
		{
			GameEvent::KeyTypedEvent* keyEvt = (GameEvent::KeyTypedEvent*)evt;
	
			if (keyEvt->key == '\b' && text.size() > 0)
			{
				text.pop_back();
			
				if (masked)
					mask.pop_back();
			}
			else if (allowedChars.find_first_of(keyEvt->key) != -1)
			{
				if (text.length() != maxChars)
				{
					text.push_back(keyEvt->key);

					if (masked)
						mask.push_back(L'*');
				}
			}
		}
		break;
	}
}

void TextBox::OnDraw()
{
	if (focused)
		textboxfocus->Draw(textbox->GetSize().width, textbox->GetSize().height, 0.0F, 1.0F);
	else
		textbox->Draw(textbox->GetSize().width, textbox->GetSize().height, 0.0F, 1.0F);
	
	if (!masked)
		textboxFont->DrawString(textbox->x + 6, textbox->y, text, D2D1::ColorF(D2D1::ColorF::Black));
	else
		textboxFont->DrawString(textbox->x + 6, textbox->y + 4, mask, D2D1::ColorF(D2D1::ColorF::Black));
}

TextBox::~TextBox()
{
	sheet = NULL;
	textbox = NULL;
}
