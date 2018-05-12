#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "Map.h"

class PathFinder
{
public:
	PathFinder(bool earthMode);
	~PathFinder();
	Node* findNodeInList(std::set<Node*>& nodeSet, Vector2int coords);
	std::vector<Vector2int> findPath(Map* map, Vector2int start, Vector2int end);
	float heuristic(Vector2int source, Vector2int target, int width, int height);
	float getPathCost();

private:
	std::vector<Vector2int> directions;
	bool earthMode;
	float pathCost;
};

