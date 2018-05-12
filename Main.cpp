#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "PathFinder.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Path Finder");
	window.setFramerateLimit(60);

	Map* map = new Map("map.txt");
	PathFinder pathFinder(true);
	Vector2int start;
	Vector2int end;
	start.x = 7;
	start.y = 23;
	end.x = 26;
	end.y = 5;
	std::vector<Vector2int> path = pathFinder.findPath(map, start, end);

	for (int i = path.size() - 1; i >= 0; i--)
	{
		std::cout << "x: " << path[i].x << " y: " << path[i].y << std::endl;
	}

	std::cout << "Path Cost: " << pathFinder.getPathCost();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		map->render(&window);
		window.display();
	}

	return 0;
}

