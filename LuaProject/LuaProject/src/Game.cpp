#include "Game.h"

GameGrid::~GameGrid()
{
	map.save("resources/map");
}


void GameGrid::init(int in_x, int in_y)
{
	backGround.setPosition(0, 0);
	backGround.setSize(sf::Vector2f(800, 8000));

	map.init("resources/map");
	luaManager.load("resources/script/yolo.lua");

	luaManager.map = &map;

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

	//luaManager.updateX();

	float x, y;

	luaManager.getPos(x, y);
	//
	p.setPos(x, y);
	//
	camPos += 1;
	backGround.setPosition(0, -camPos);
	//
	//type collision = NONE;
	//type boons = NONE;
	//
	//map.mapCollide(&p, &collision, &boons);
	//
	//luaManager.sendCollison(collision, boons, false);

	//luaManager.updateY();
	//
	//luaManager.getPos(x, y);
	//
	//p.setPos(x, y);
	//
	//map.mapCollide(&p, &collision, &boons);
	//
	//luaManager.sendCollison(collision, boons, true);

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

void GameGrid::rektedit(int x, int y, int type)
{
	map.editRekts(x, y, type);
}

int GameGrid::getCampos()
{
	return camPos;
}