#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "Map.h"

class PathFinder
{
public:
	PathFinder();
	~PathFinder();
	Node* findNodeInList(std::set<Node*>& nodeSet, Vector2int coords);
	std::vector<Vector2int> findPath(Map* map, Vector2int start, Vector2int end);
	float heuristic(Vector2int source, Vector2int target);

private:
	std::vector<Vector2int> directions;
};

