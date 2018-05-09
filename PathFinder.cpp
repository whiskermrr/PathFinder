#include "stdafx.h"
#include "PathFinder.h"


PathFinder::PathFinder(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	directions = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};

	for (int i = 0; i < height; i++)
	{
		std::vector<Node*> row;
		for (int j = 0; j < width; j++)
		{
			Vector2int coords;
			coords.x = i;
			coords.y = j;
			row.push_back(new Node(coords, 1));
		}
		mapNodes.push_back(row);
		row.clear();
	}
}

std::vector<Vector2int> PathFinder::findPath(Vector2int startCoords, Vector2int endCoords)
{
	Node* currentNode = nullptr;
	std::set<Node*> openSet, closedSet;
	currentNode = findNodeOnMap(startCoords);
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

			unsigned int totalCost = currentNode->g + ((i < 4) ? currentNode->weight : currentNode->weight * 1.5f);

			Node* succesor = findNodeInList(openSet, newCoords);

			if (succesor == nullptr) 
			{
				succesor = findNodeOnMap(newCoords);
				succesor->parent = currentNode;
				succesor->g = totalCost;
				succesor->h = heuristic(succesor->coords, endCoords);
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
		path.push_back(currentNode->coords);
		currentNode = currentNode->parent;
	}

	return path;
}

unsigned int PathFinder::heuristic(Vector2int source, Vector2int target)
{
	return sqrt(pow(source.x - target.x, 2) + pow(source.y - target.y, 2));
}

Node* PathFinder::findNodeOnMap(Vector2int coords)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (mapNodes[i][j]->coords == coords)
				return mapNodes[i][j];
		}
	}

	return nullptr;
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

void PathFinder::printMap()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << mapNodes[i][j]->weight << " ";
		}
		std::cout << std::endl;
	}
}


PathFinder::~PathFinder()
{
}
