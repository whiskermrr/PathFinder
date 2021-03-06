#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathManager.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Path Finder");
	window.setFramerateLimit(60);
	sf::Clock clock;
	std::string fileName = "map2.txt";

	PathManager pathManager(fileName);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asMilliseconds() > 500)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				pathManager.findPath(true);
				std::cout << "Path cost: " <<
					((pathManager.getPathCost()) > 0 ? std::to_string(pathManager.getPathCost()) : "Path not found.")
					<< std::endl;
				clock.restart();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				float mouseX = sf::Mouse::getPosition(window).x;
				float mouseY = sf::Mouse::getPosition(window).y;
				pathManager.setStart(mouseX, mouseY);
				clock.restart();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				float mouseX = sf::Mouse::getPosition(window).x;
				float mouseY = sf::Mouse::getPosition(window).y;
				pathManager.setEnd(mouseX, mouseY);
				clock.restart();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				pathManager.resetMap(fileName);
			}
		}
		
		window.clear();
		pathManager.render(&window);
		window.display();
	}

	return 0;
}

