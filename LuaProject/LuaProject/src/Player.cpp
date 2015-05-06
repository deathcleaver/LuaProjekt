#include "Player.h"

Player::Player()
{
	playerCube.setPosition(0, 0);
	playerCube.setSize(sf::Vector2f(40, 40));

	tex.loadFromFile("resources/box.png");
	playerCube.setTexture(&tex, true);
	playerCube.setTextureRect(sf::IntRect(0, 0, 40, 40));
	playerCube.setFillColor(sf::Color::White);

	collisionRect = Rect(0, 0, 0.4);
}

void Player::setPos(float x, float y)
{
	playerCube.setPosition(x, y);
	collisionRect.update(x, y);
	px = x;
	py = y;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(playerCube, states);
}

void Player::getPos(float* x, float* y)
{
	*x = px;
	*y = py;
}

Player::~Player()
{

}