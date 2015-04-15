#include "lua.hpp"
#include <iostream>

#include <string>

#include "../SFML/Graphics.hpp"

#include "GameGrid.h"

int main()
{

	sf::RenderWindow rw;

	sf::ContextSettings setting;

	rw.create(sf::VideoMode(800, 800), "title", sf::Style::Close,  setting);


	sf::Event sfEvent;

	GameGrid g;

	g.init(16, 16);
	g.setBackground("resources/background.png");

	while (rw.isOpen())
	{

		rw.pollEvent(sfEvent);

		switch (sfEvent.type)
		{
		case sf::Event::Closed:
			rw.close();
			break;
		default:
			break;
		}


		rw.clear();

		rw.draw(g);

		rw.display();
	}

	return 0;
}