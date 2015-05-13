#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Player.h"

#include "rect.h"
#include "../SFML/Graphics.hpp"

using namespace std;

enum type
{
	NONE = char('0'),
	UPGRADE_SPEED,
	UPGRADE_TIME,
	COLLISON,
	DAMAGE,
	
};

struct MapTile
{
	type mapType;
	Rect rect;
	int x, y;
	
	sf::RectangleShape backGround;
	sf::Texture bgTexture;
	bool taken;

	MapTile()
	{

	}

	void init(int _x, int _y, type _t)
	{
		x = _x;
		y = _y;
		rect = Rect(x + 0.5f, y + 0.5f, 0.5f);
		mapType = _t;

		if (mapType == type::COLLISON)
			bgTexture.loadFromFile("resources/box.png");
		else if (mapType == type::DAMAGE)
			bgTexture.loadFromFile("resources/damage.png");
		else if (mapType == type::UPGRADE_SPEED)
			bgTexture.loadFromFile("resources/speed.png");
		else if (mapType == type::UPGRADE_TIME)
			bgTexture.loadFromFile("resources/time.png");
		backGround.setSize(sf::Vector2f(48, 48));
		backGround.setTexture(&bgTexture, false);
		backGround.setTextureRect(sf::IntRect(0, 0, 50, 50));
		backGround.setFillColor(sf::Color::White);
		taken = false;

	}

	void draw(float pos, sf::RenderTarget& target, sf::RenderStates states)
	{
		float thisPos = (y * 50) + 000;
		float renderPosY = (thisPos - pos) + 800;

		backGround.setPosition(x * 50, renderPosY);

		if (!taken)
			target.draw(backGround);

	}

};

struct Map 
{
	MapTile*** mapTiles;
	int maxCap = 500;
	int count = 0;
	
	Map()
	{

	}

	~Map()
	{
	
	}

	void mapCollide(Player* player, type* collideMap, type* collideSpecial)
	{

		float startX, startY, half;
		player->getPos(&startX, &startY);
		half = 0.4;
		int X = ((startX - half) / 50);
		int Y = ((startY - half - 800.0f)/ 50);
		int searchRangeX = (half * 4 + 0.5f);
		int searchRangeY = searchRangeX + Y + 1;
		searchRangeX += X + 1;
		
		*collideMap = NONE;
		*collideSpecial = NONE;
		float px, py;
		player->getPos(&px, &py);
		player->collisionRect.updatePlayerRekt(px, py);

		for (X - 1; X < searchRangeX; X++)
		{
			for (int tempY = Y - 1; tempY < searchRangeY; tempY++)
			{
				if (X > -1 && X < 16 && tempY > -1 && tempY < count)
				{
					if (mapTiles[tempY][X])
					{
						if (mapTiles[tempY][X]->taken)
							continue;

						//if collide
						if (mapTiles[tempY][X]->rect.intersects(&(player->collisionRect)))
						{
							switch (mapTiles[tempY][X]->mapType)
							{
							case(COLLISON) :
								if (*collideMap != DAMAGE)
									*collideMap = COLLISON;
								break;
							case(DAMAGE) :
								*collideMap = DAMAGE;
								return; // return, you'll be dead anyways
								break;
							case(UPGRADE_SPEED) :
								*collideSpecial = UPGRADE_SPEED;
								mapTiles[tempY][X]->taken = true;
								break;
							case(UPGRADE_TIME) :
								*collideSpecial = UPGRADE_TIME;
								mapTiles[tempY][X]->taken = true;
								break;
							}
						}
					}
				}
			}
		}
	}

	void mapReset()
	{
		for (int y = 0; y < count; y++)
		{
			for (int x = 0; x < 16; x++)
			{
				if (mapTiles[y][x])
					mapTiles[y][x]->taken = false;
			}
		}
	}

	void init(string fileName)
	{
		ifstream infile(fileName);

		if (infile.is_open())
		{
			// read crap

			infile >> count;
			string t;
			getline(infile, t);

			mapTiles = new MapTile**[maxCap];
			for (size_t y = 0; y < count && y < maxCap; y++)
			{
				mapTiles[y] = new MapTile*[16];
				
				string line;
				getline(infile, line);
				
				for (size_t x = 0; x < 16; x++)
				{
					if (line[x] == NONE)
					{
						mapTiles[y][x] = nullptr;
					}
					else if (line[x] == COLLISON)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, COLLISON);
						mapTiles[y][x]->rect = Rect(x + 0.5f, y + 0.5f, 0.5f);
					}
					else if (line[x] == UPGRADE_SPEED)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, UPGRADE_SPEED);
						mapTiles[y][x]->rect = Rect(x, y, 0.5);
					}
					else if (line[x] == UPGRADE_TIME)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, UPGRADE_TIME);
						mapTiles[y][x]->rect = Rect(x, y, 0.5);
					}
					else if (line[x] == DAMAGE)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, DAMAGE);
						mapTiles[y][x]->rect = Rect(x, y, 0.5);
					}
					else
					{
						mapTiles[y][x] = nullptr;
					}
				}
			}
		}
	}

	void save(string fileName)
	{
		fstream out;

		out.open(fileName, std::ofstream::out | std::ofstream::trunc);
		
		if (out.is_open())
		{
			out << count << endl;
			for (int n = 0; n < count; n++)
			{
				for (int k = 0; k < 16; k++)
				{
					if (mapTiles[n][k])
					{
						out << char(mapTiles[n][k]->mapType);
					}
					else
						out <<char(NONE);
				}
				out << endl;
			}
		}
	}

	void mapDraw(float camY, sf::RenderTarget& target, sf::RenderStates states) const
	{
		float infloat = camY;

		int index = (camY / 50);

		for (int i = index - 16; i  < index + 1; i ++)
		{
			if (i >= 0 && i < count)
			{
				for (int x = 0; x < 16; x++)
				{
					if (mapTiles[i][x])
						mapTiles[i][x]->draw(infloat, target, states);
				}
			}
		}

	}

	void editRekts(int x, int y, int intype)
	{
		if (x > -1 && y > -1 &&
			x < 16 && y < maxCap)
		{
			// --- Add new lines if needed
			int addlines = y - (count -1);
			if (addlines > 0 && count + addlines < maxCap)
			{
				for (int n = 0; n < addlines; n++)
				{
					mapTiles[count + n] = new MapTile*[16];


					for (int k = 0; k < 16; k++)
					{
						mapTiles[count + n][k] = 0;
					}
				}
				count += addlines;
			}

			// --- Edit the selected tile
			if (!mapTiles[y][x])
				mapTiles[y][x] = new MapTile();

			if (intype == type::NONE)
			{
				delete mapTiles[y][x];
				mapTiles[y][x] = 0;
			}
			else
			mapTiles[y][x]->init(x, y, type(intype));
		}
	}
};


#endif