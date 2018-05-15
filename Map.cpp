#include "Map.h"


Map::Map(std::string fileName)
{
	std::fstream file("resources/" + fileName);

	this->width = 0;
	this->height = 0;
	this->startNode = nullptr;
	this->endNode = nullptr;

	if (file.is_open())
	{
		char x;

		while (!file.eof())
		{
			file >> x;

			if (isdigit(x))
			{
				Vector2int coords;
				coords.x = width;
				coords.y = height;
				Node* node = new Node(coords, x - '0');
				nodesMap.push_back(node);


				width++;
			}
			if (file.peek() == '\n')
			{
				height++;
				width = 0;
			}
		}
		height++;
	}
}

Node* Map::findNodeOnMap(Vector2int coords)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (this->nodesMap.at(i * width + j)->coords == coords)
				return this->nodesMap.at(i * width + j);
		}
	}

	return nullptr;
}

void Map::render(sf::RenderWindow* window)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			window->draw(*this->nodesMap.at(i * width + j));
		}
	}
}

unsigned int Map::getWidth()
{
	return this->width;
}

unsigned int Map::getHeight()
{
	return this->height;
}

std::vector<Node*>& Map::getNodesMap()
{
	return this->nodesMap;
}

void Map::setStart(float x, float y)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Node* node = this->nodesMap.at(i * width + j);
			if (node->getGlobalBounds().contains(x, y)
				&& !node->isWall())
			{
				if (this->startNode != nullptr)
					startNode->loadTexture("floor.png");
				this->startNode = node;
				this->startNode->loadTexture("start.png");
			}
		}
	}
}

void Map::setEnd(float x, float y)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Node* node = this->nodesMap.at(i * width + j);
			if (node->getGlobalBounds().contains(x, y)
				&& !node->isWall())
			{
				if (this->endNode != nullptr)
					endNode->loadTexture("floor.png");
				this->endNode = node;
				this->endNode->loadTexture("end.png");
			}
		}
	}
}

Node* Map::getStartNode()
{
	return this->startNode;
}

Node* Map::getEndNode()
{
	return this->endNode;
}

Map::~Map()
{
}
