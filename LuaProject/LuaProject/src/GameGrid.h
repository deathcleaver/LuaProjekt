#ifndef GAMEGRID_H
#define GAMEGRID_H

#include "../SFML/Graphics.hpp"
#include <string>

class GameGrid : public sf::Drawable
{

public:

	void init(int x, int y);

	void setBackground(std::string texturePath);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	//sf::Sprite backGround;
	sf::RectangleShape backGround;
	sf::Texture bgTexture;

	sf::RectangleShape grid[16][16];

};

#endif