#include "PathManager.h"



PathManager::PathManager(std::string fileName)
{
	this->map = new Map(fileName);
}

std::vector<Vector2int> PathManager::findPath(bool earthMode)
{
	PathFinder pathFinder(earthMode);
	std::vector<Vector2int> path = pathFinder.findPath(this->map, 
													this->map->getStartNode()->coords, 
													this->map->getEndNode()->coords
													);
	pathCost = pathFinder.getPathCost();

	return path;
}

void PathManager::setStart(float x, float y)
{
	this->map->setStart(x, y);
}

void PathManager::setEnd(float x, float y)
{
	this->map->setEnd(x, y);
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
