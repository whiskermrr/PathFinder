#include "stdafx.h"
#include "PathFinder.h"


PathFinder::PathFinder()
{
	directions = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

std::vector<Vector2int> PathFinder::findPath(Map* map, Vector2int startCoords, Vector2int endCoords)
{
	Node* currentNode = nullptr;
	unsigned int width = map->getWidth();
	unsigned int height = map->getHeight();
	std::set<Node*> openSet, closedSet;
	currentNode = map->findNodeOnMap(startCoords);
	currentNode->h = heuristic(startCoords, endCoords);
	openSet.insert(currentNode);

	while (!openSet.empty())
	{
		currentNode = *openSet.begin();
		
		for (auto node : openSet)
		{
			if (node->getTotalScore() <= currentNode->getTotalScore())
				currentNode = node;
		}

		if (currentNode->coords == endCoords)
			break;


		closedSet.insert(currentNode);
		openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));

		for (int i = 0; i < directions.size(); i++)
		{
			Vector2int newCoords = currentNode->coords + directions[i];

			if (newCoords.x < 0 || newCoords.x >= height || newCoords.y < 0 || newCoords.y >= width || findNodeInList(closedSet, newCoords))
			{
				continue;
			}

			float totalCost = currentNode->g + ((i < 4) ? (currentNode->weight + 1) : (currentNode->weight + 1) * 1.5f);

			Node* succesor = findNodeInList(openSet, newCoords);

			if (succesor == nullptr)
			{
				succesor = map->findNodeOnMap(newCoords);
				if (succesor->isWall())
					continue;
				succesor->parent = currentNode;
				succesor->g = totalCost;
				succesor->h = heuristic(succesor->coords, endCoords);
				succesor->setVisited();
				openSet.insert(succesor);
			}
			else if(succesor->g > totalCost)
			{
				succesor->parent = currentNode;
				succesor->g = totalCost;
			}
		}
	}

	std::vector<Vector2int> path;
	while (currentNode != nullptr)
	{
		currentNode->setPath();
		path.push_back(currentNode->coords);
		currentNode = currentNode->parent;
	}

	return path;
}

float PathFinder::heuristic(Vector2int source, Vector2int target)
{
	return sqrt(pow(source.x - target.x, 2) + pow(source.y - target.y, 2));
	//return std::max(abs(source.x - target.x), abs(source.y - target.y));
	//return abs(source.x - target.x) + abs(source.y - target.y);
}

Node* PathFinder::findNodeInList(std::set<Node*>& nodeSet, Vector2int coords)
{
	for (auto node : nodeSet)
	{
		if (node->coords == coords)
			return node;
	}
	return nullptr;
}

PathFinder::~PathFinder()
{
}
