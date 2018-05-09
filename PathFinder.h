#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "Node.h"

class PathFinder
{
public:
	PathFinder(unsigned int width, unsigned int height);
	~PathFinder();
	Node* findNodeInList(std::set<Node*>& nodeSet, Vector2int coords);
	Node* findNodeOnMap(Vector2int coords);
	std::vector<Vector2int> findPath(Vector2int start, Vector2int end);
	void printMap();
	unsigned int heuristic(Vector2int source, Vector2int target);

private:
	unsigned int width, height;
	std::vector<Vector2int> directions;
	std::vector<std::vector<Node*>> mapNodes;
};

