#include "Player.h"

Player::Player()
{
	playerCube.setPosition(0, 0);
	playerCube.setSize(sf::Vector2f(40, 40));

	tex.loadFromFile("resources/box.png");
	playerCube.setTexture(&tex, true);
	playerCube.setTextureRect(sf::IntRect(0, 0, 40, 40));
	playerCube.setFillColor(sf::Color::White);

}

void Player::setPos(float x, float y)
{
	playerCube.setPosition(x, y);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(playerCube, states);
}

Player::~Player()
{

}