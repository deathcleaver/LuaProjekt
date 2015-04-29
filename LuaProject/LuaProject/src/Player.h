#ifndef PLAYER_H
#define PLAYER_H

#include "../SFML/Graphics.hpp"

#include "rect.h"

class Player : public sf::Drawable
{

public:

	Player();
	~Player();

	void setPos(float x, float y);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Rect collisionRect;

private:

	float px, py;


	sf::RectangleShape playerCube;
	sf::Texture tex;
};

#endif