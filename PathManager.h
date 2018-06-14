#pragma once
#include "PathFinder.h"

class PathManager
{
public:
	PathManager(std::string fileName);
	std::vector<Vector2int> findPath(bool earthMode);
	float getPathCost();
	void render(sf::RenderWindow* window);
	void setStart(float x, float y);
	void setEnd(float x, float y);
	void resetMap(std::string fileName);
	~PathManager();

private:
	Map * map;
	float pathCost;
};

