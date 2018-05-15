#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathManager.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Path Finder");
	window.setFramerateLimit(60);
	sf::Sprite sprite;
	sprite.setPosition(10, 12);

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
			pathManager.findPath(true);
			std::cout << "Path cost: " << 
				((pathManager.getPathCost()) > 0 ? std::to_string(pathManager.getPathCost()) : "Path not found.") 
				<< std::endl;
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;
			pathManager.setStart(mouseX, mouseY);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;
			pathManager.setEnd(mouseX, mouseY);

		}
		
		window.clear();
		pathManager.render(&window);
		window.display();
	}

	return 0;
}

