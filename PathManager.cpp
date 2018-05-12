#include "PathManager.h"



PathManager::PathManager(std::string fileName)
{
	this->map = new Map(fileName);
	start.x = 7;
	start.y = 22;
	end.x = 24;
	end.y = 12;
}

std::vector<Vector2int> PathManager::findPath(bool earthMode)
{
	PathFinder pathFinder(earthMode);
	std::vector<Vector2int> path = pathFinder.findPath(this->map, this->start, this->end);
	pathCost = pathFinder.getPathCost();

	return path;
}

void PathManager::setStart(float x, float y)
{
	this->start = map->setStart(x, y);
}

void PathManager::setEnd(float x, float y)
{
	this->end = map->setEnd(x, y);
}

void PathManager::render(sf::RenderWindow* window)
{
	this->map->render(window);
}

float PathManager::getPathCost()
{
	return this->pathCost;
}

PathManager::~PathManager()
{
}
