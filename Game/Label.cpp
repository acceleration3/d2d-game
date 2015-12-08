#include "stdafx.h"
#include "Label.h"


Label::Label(std::wstring text, int size, BYTE r, BYTE g, BYTE b) : text(text), r(r), g(g), b(b)
{
	font = new Font(L"Pokemon DPPt", size);
}

void Label::OnDraw()
{
	int normalColor = MakeInt(r, g, b);
	int maxComponent = (r > g ? (r > b ? r : b) : (g > b ? g : b));
	int shadowColor = 0;

	if (maxComponent < 200)
		//shadowColor = (normalColor & 0x7f7f7f) << 1;
		shadowColor = MakeInt(176, 176, 182);
	else
		shadowColor = (normalColor & 0xfefefe) >> 1;

	font->DrawString(this->x + 2, this->y, this->text, D2D1::ColorF(shadowColor, 1.0F));
	font->DrawString(this->x, this->y + 2, this->text, D2D1::ColorF(shadowColor, 1.0F));
	font->DrawString(this->x + 2, this->y + 2, this->text, D2D1::ColorF(shadowColor, 1.0F));
	font->DrawString(this->x, this->y, this->text, D2D1::ColorF(normalColor, 1.0F));
}

int Label::MakeInt(BYTE r, BYTE g, BYTE b)
{
	int firstPart = (r & 0x0000FF) << 16;
	int secondPart = (g & 0x0000FF) << 8;
	int thirdPart = (b & 0x0000FF);

	return firstPart + secondPart + thirdPart;
}

Label::~Label()
{
	delete font;
	font = NULL;
}
