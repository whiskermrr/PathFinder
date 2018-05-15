#include "stdafx.h"
#include "PathFinder.h"


PathFinder::PathFinder(bool earthMode)
{
	this->earthMode = earthMode;
	this->pathCost = 0;

	directions = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

std::vector<Vector2int> PathFinder::findPath(Map* map, Vector2int startCoords, Vector2int endCoords)
{
	this->pathCost = 0;
	Node* currentNode = nullptr;
	unsigned int width = map->getWidth();
	unsigned int height = map->getHeight();
	std::set<Node*> openSet, closedSet;
	currentNode = map->findNodeOnMap(startCoords);
	currentNode->h = heuristic(startCoords, endCoords, width, height);
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
		{
			pathCost = currentNode->g;
			break;
		}

		closedSet.insert(currentNode);
		openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));

		for (int i = 0; i < directions.size(); i++)
		{
			Vector2int newCoords = currentNode->coords + directions[i];

			if (this->earthMode)
			{
				if (newCoords.x < 0)			newCoords.x = width - 1;
				else if (newCoords.x >= width)	newCoords.x = 0;
				if (newCoords.y < 0)			newCoords.y = height - 1;
				else if (newCoords.y >= height)	newCoords.y = 0;

				if (findNodeInList(closedSet, newCoords))
				{
					continue;
				}
			}
			else
			{
				if (newCoords.x < 0 || newCoords.x >= height || newCoords.y < 0 || newCoords.y >= width || findNodeInList(closedSet, newCoords))
				{
					continue;
				}
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
				succesor->h = heuristic(succesor->coords, endCoords, width, height);
				succesor->setAsVisited();
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

	if (pathCost > 0)
	{
		while (currentNode != nullptr)
		{
			currentNode->setAsPath();
			path.push_back(currentNode->coords);
			currentNode = currentNode->parent;
		}
	}
	
	return path;
}


float PathFinder::heuristic(Vector2int source, Vector2int target, int width, int height)
{
	if (this->earthMode)
	{
		float distanceX = std::min(abs(source.x - target.x), width - abs(source.x - target.x));
		float distanceY = std::min(abs(source.y - target.y), height - abs(source.y - target.y));
		return sqrt(pow(distanceX, 2) + pow(distanceY, 2));
	}

	return sqrt(pow(source.x - target.x, 2) + pow(source.y - target.y, 2));
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

float PathFinder::getPathCost()
{
	return this->pathCost;
}

PathFinder::~PathFinder()
{
}
