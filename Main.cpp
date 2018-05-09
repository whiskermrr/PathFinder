// PathFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathFinder.h"


int main()
{
	PathFinder pathFinder(10, 10);
	Vector2int start, end;
	start.x = 2;
	start.y = 1;
	end.x = 7;
	end.y = 8;
	pathFinder.printMap();

	std::vector<Vector2int> path = pathFinder.findPath(start, end);

	for (Vector2int coords : path)
	{
		std::cout << "x: " << coords.x << " y: " << coords.y << std::endl;
	}

	system("PAUSE");
	return 0;
}

