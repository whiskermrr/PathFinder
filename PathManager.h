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
	~PathManager();

private:
	Map * map;
	Vector2int start;
	Vector2int end;
	float pathCost;
};

