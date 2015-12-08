#include "stdafx.h"
#include "Panel.h"

Bitmap* Panel::panel = NULL;
int Panel::currentSkin = 0;

Panel::Panel(int tileWidth, int tileHeight) : tileWidth(tileWidth), tileHeight(tileHeight)
{
	if (panel == NULL)
		ChangeSkin(1);
}

void Panel::SetPosition(int x, int y)
{
	UIControl::SetPosition(x, y);
	panel->x = x;
	panel->y = y;
}

void Panel::ChangeSkin(int index)
{
	std::wstringstream wss;
	wss << L"panel" << index << L".png";
	
	int tempX, tempY;
	
	if (panel != NULL)
	{
		tempX = panel->x;
		tempY = panel->y;
		ContentLoader::LoadContent(wss.str(), panel);
		panel->x = tempX;
		panel->y = tempY;
	}
	else
	{
		ContentLoader::LoadContent(wss.str(), panel);
	}

	currentSkin = index;
}

void Panel::OnDraw()
{
	Bitmap* tile1 = new Bitmap(16, 16);
	Bitmap* tile2 = new Bitmap(16, 16);
	Bitmap* tile3 = new Bitmap(16, 16);
	Bitmap* tile4 = new Bitmap(16, 16);
	Bitmap* tile5 = new Bitmap(16, 16);
	Bitmap* tile6 = new Bitmap(16, 16);
	Bitmap* tile7 = new Bitmap(16, 16);
	Bitmap* tile8 = new Bitmap(16, 16);
	Bitmap* tile9 = new Bitmap(16, 16);

	//Corners
	panel->CopyTo(tile1, 0, 0, 16, 16, 0, 0);
	tile1->x = this->x;
	tile1->y = this->y;
	tile1->Draw(TILE_SIZE, TILE_SIZE);

	panel->CopyTo(tile3, 0, 0, 16, 16, 36, 0);
	tile3->x = this->x + (this->tileWidth - 1) * TILE_SIZE;
	tile3->y = this->y;
	tile3->Draw(TILE_SIZE, TILE_SIZE);

	panel->CopyTo(tile7, 0, 0, 16, 16, 0, 36);
	tile7->x = this->x;
	tile7->y = this->y + (this->tileHeight - 1) * TILE_SIZE;
	tile7->Draw(TILE_SIZE, TILE_SIZE);

	panel->CopyTo(tile9, 0, 0, 16, 16, 36, 36);
	tile9->x = this->x + (this->tileWidth - 1) * TILE_SIZE;
	tile9->y = this->y + (this->tileHeight - 1) * TILE_SIZE;
	tile9->Draw(TILE_SIZE, TILE_SIZE);

	//Edges
	panel->CopyTo(tile2, 0, 0, 16, 16, 18, 0);
	tile2->y = this->y;
	for (int i = 1; i < tileWidth - 1; i++)
	{
		tile2->x = this->x + (TILE_SIZE * i);
		tile2->Draw(TILE_SIZE, TILE_SIZE);
	}
	
	panel->CopyTo(tile4, 0, 0, 16, 16, 0, 18);
	tile4->x = this->x;
	for (int i = 1; i < tileHeight - 1; i++)
	{
		tile4->y = this->y + (TILE_SIZE * i);
		tile4->Draw(TILE_SIZE, TILE_SIZE);
	}

	panel->CopyTo(tile6, 0, 0, 16, 16, 36, 18);
	tile6->x = this->x + (this->tileWidth - 1) * TILE_SIZE;

	for (int i = 1; i < tileHeight - 1; i++)
	{
		tile6->y = this->y + (TILE_SIZE * i);
		tile6->Draw(TILE_SIZE, TILE_SIZE);
	}

	panel->CopyTo(tile8, 0, 0, 16, 16, 18, 36);
	tile8->y = this->y + (this->tileHeight - 1) * TILE_SIZE;

	for (int i = 1; i < tileWidth - 1; i++)
	{
		tile8->x = this->x + (TILE_SIZE * i);
		tile8->Draw(TILE_SIZE, TILE_SIZE);
	}

	//Center
	panel->CopyTo(tile8, 0, 0, 16, 16, 18, 18);
	tile8->x = this->x + TILE_SIZE;
	tile8->y = this->y + TILE_SIZE;
	tile8->Draw((this->tileWidth - 2) * TILE_SIZE, (this->tileHeight - 2) * TILE_SIZE);

	delete tile1;
	delete tile2;
	delete tile3;
	delete tile4;
	delete tile5;
	delete tile6;
	delete tile7;
	delete tile8;
	delete tile9;
}


Panel::~Panel()
{
}
