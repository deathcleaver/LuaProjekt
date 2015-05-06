#include "Game.h"

GameGrid::~GameGrid()
{
	map.save("resources/map");
}


void GameGrid::init(int in_x, int in_y)
{
	backGround.setPosition(0, 0);
	backGround.setSize(sf::Vector2f(800, 8000));

	for (size_t y = 0; y < 16; y++)
	{
		for (size_t x = 0; x < 16; x++)
		{
			grid[y][x].setPosition(x * 50, y * 50);
			grid[y][x].setSize(sf::Vector2f(48, 48));
			grid[y][x].setFillColor(sf::Color(255, 255, 255, 255));
		}
	}

	map.init("resources/map");
	luaManager.load("resources/script/yolo.lua");

	camPos = 0;

}

void GameGrid::setBackground(std::string texturePath)
{
	
	bgTexture.loadFromFile(texturePath);
	backGround.setTexture(&bgTexture, true);
	backGround.setTextureRect(sf::IntRect(0, 0, 800, 800));
	backGround.setFillColor(sf::Color::White);

}

void GameGrid::update()
{
	luaManager.update();

	float x, y;

	luaManager.getPos(x, y);

	p.setPos(x, y);

	camPos += 1;
	backGround.setPosition(0, -camPos);

	type collision = NONE;
	type boons = NONE;

	map.mapCollide(&p, &collision, &boons);

	if (collision != NONE)
		std::cout << "Collided" << std::endl;
	else
		std::cout << "No ze collision" << std::endl;

	//std::cout << boons << std::endl;

	p.setPos(x, y - camPos);

}


void GameGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(backGround);

	map.mapDraw(camPos, target, states);
	p.draw(target, states);
	

	/*for (size_t x = 0; x < 16; x++)
	{
		for (size_t y = 0; y < 16; y++)
		{
			target.draw(grid[x][y]);
		}
	}*/
}