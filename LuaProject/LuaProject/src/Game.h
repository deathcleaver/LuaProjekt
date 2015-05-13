#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "../SFML/Graphics.hpp"
#include <string>

#include "Map.h"
#include "LuaManager.h"
#include "Player.h"

class GameGrid : public sf::Drawable
{

public:

	void init(int x, int y);

	void setBackground(std::string texturePath);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	~GameGrid();

	void update();

	LuaManager luaManager;

private:

	Map map;

	Player p;

	float camPos;

	//sf::Sprite backGround;
	sf::RectangleShape backGround;
	sf::Texture bgTexture;

};

#endif