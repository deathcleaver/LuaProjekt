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
			default:
				break;
			}
		default:
			break;
		}


		rw.clear();
		g.update();
		rw.draw(g);

		rw.display();
	}

	return 0;
}