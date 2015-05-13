#include "lua.hpp"
#include <iostream>

#include <string>

#include "../SFML/Graphics.hpp"

#include "Game.h"

int main()
{

	sf::RenderWindow rw;

	sf::ContextSettings setting;

	rw.create(sf::VideoMode(800, 800), "title", sf::Style::Close,  setting);

	rw.setVerticalSyncEnabled(true);

	sf::Event sfEvent;

	GameGrid g;

	g.init(16, 16);
	g.setBackground("resources/background2.png");

	bool editState = false;

	while (rw.isOpen())
	{

		rw.pollEvent(sfEvent);

		switch (sfEvent.type)
		{
		case sf::Event::Closed:
			rw.close();
			break;
		case sf::Event::KeyPressed:
			switch (sfEvent.key.code)
			{
			case sf::Keyboard::W:
				g.luaManager.setKeyState('w', true);
				break;
			case sf::Keyboard::A:
				g.luaManager.setKeyState('a', true);
				break;
			case sf::Keyboard::S:
				g.luaManager.setKeyState('s', true);
				break;
			case sf::Keyboard::D:
				g.luaManager.setKeyState('d', true);
				break;
			case sf::Keyboard::Return:
				{
					g.luaManager.toggleEditState();
					editState = !editState;
				}
				break;
			case sf::Keyboard::Space:
			{
					g.luaManager.togglePauseState();
					editState = !editState;
			}
				break;
			default:
				break;
			}
			
			break;
		case sf::Event::KeyReleased:
			switch (sfEvent.key.code)
			{
			case sf::Keyboard::W:
				g.luaManager.setKeyState('w', false);
				break;
			case sf::Keyboard::A:
				g.luaManager.setKeyState('a', false);
				break;
			case sf::Keyboard::S:
				g.luaManager.setKeyState('s', false);
				break;
			case sf::Keyboard::D:
				g.luaManager.setKeyState('d', false);
				break;
			case sf::Keyboard::Return:
				break;
			default:
				break;
			}
		default:
			break;
		}

		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && editState)
		{
			int in_X, in_Y;
			in_X = (sf::Mouse::getPosition().x - rw.getPosition().x ) / 50;
			in_Y = (sf::Mouse::getPosition().y + g.getCampos() - 800 - rw.getPosition().y - 50 ) / 50;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
				g.rektedit(in_X, in_Y, type::UPGRADE_SPEED);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
				g.rektedit(in_X, in_Y, type::UPGRADE_TIME);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
				g.rektedit(in_X, in_Y, type::DAMAGE);

			else
				g.rektedit(in_X, in_Y, type::COLLISON);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && editState)
		{
			int in_X, in_Y;
			in_X = (sf::Mouse::getPosition().x - rw.getPosition().x) / 50;
			in_Y = (sf::Mouse::getPosition().y + g.getCampos() - 800 - rw.getPosition().y - 50) / 50;

			g.rektedit(in_X, in_Y, type::NONE);
		}

		rw.clear();
		g.update();
		rw.draw(g);

		rw.display();
	}

	return 0;
}