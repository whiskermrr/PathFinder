#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathManager.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Path Finder");
	window.setFramerateLimit(60);

	PathManager pathManager("map.txt");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			pathManager.findPath(false);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			float mouseX = sf::Mouse::getPosition().x;
			float mouseY = sf::Mouse::getPosition().y;
			pathManager.setStart(mouseX, mouseY);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			float mouseX = sf::Mouse::getPosition().x;
			float mouseY = sf::Mouse::getPosition().y;
			pathManager.setEnd(mouseX, mouseY);

		}

		window.clear();
		pathManager.render(&window);
		window.display();
	}

	return 0;
}

