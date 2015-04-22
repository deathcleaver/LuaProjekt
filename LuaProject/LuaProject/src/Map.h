#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
	int x, y;

	MapTile()
	{

	}

	void init(int _x, int _y, type _t)
	{
		x = _x;
		y = _y;
		mapType = _t;
	}

	void draw(float pos, sf::RenderTarget& target, sf::RenderStates states)
	{
		float thisPos = (y * 50) + 000;
		float renderPosY = (thisPos - pos) + 400;

		sf::RectangleShape backGround;
		sf::Texture bgTexture;
		
		bgTexture.loadFromFile("resources/box.png");
		backGround.setPosition(x * 50, renderPosY);
		backGround.setSize(sf::Vector2f(48, 48));
		backGround.setTexture(&bgTexture, false);
		backGround.setTextureRect(sf::IntRect(0, 0, 50, 50));
		backGround.setFillColor(sf::Color::White);
		
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
					}
					else if (line[x] == UPGRADE_SPEED)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, UPGRADE_SPEED);
					}
					else if (line[x] == UPGRADE_TIME)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, UPGRADE_TIME);
					}
					else if (line[x] == DAMAGE)
					{
						mapTiles[y][x] = new MapTile();
						mapTiles[y][x]->init(x, y, DAMAGE);
					}
					else
					{
						mapTiles[y][x] = nullptr;
					}
				}
			}
		}

	}

	void mapDraw(float camY, sf::RenderTarget& target, sf::RenderStates states) const
	{
		float infloat = camY;

		int index = (camY / 50);

		for (int i = index - 9; i  < index + 9; i ++)
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
};


#endif