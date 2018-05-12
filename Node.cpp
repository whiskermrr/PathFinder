#include "stdafx.h"
#include "Node.h"


bool Vector2int::operator==(Vector2int& coords)
{
	return (x == coords.x && y == coords.y);
}

Vector2int Vector2int::operator+(Vector2int& coords)
{
	Vector2int newCoords;
	newCoords.x = x + coords.x;
	newCoords.y = y + coords.y;

	return newCoords;
}

Node::Node()
{
}

Node::Node(Vector2int coords, int weight)
{
	this->coords = coords;
	this->weight = weight;
	parent = nullptr;
	this->texture = new sf::Texture();
	g = h = 0;

	std::string fileName;

	switch (weight)
	{
	case 0:
		fileName = "floor.png";
		break;
	case 1:
		fileName = "wall.png";
		break;
	default:
		fileName = "floor.png";
		break;
	}

	loadTexture(fileName);
	this->setPosition(this->coords.x * 16, this->coords.y * 16);
}

void Node::loadTexture(std::string fileName)
{
	this->texture->loadFromFile("resources/" + fileName);
	this->setTexture(*this->texture, true);
}

unsigned int Node::getTotalScore()
{
	return g + h;
}

bool Node::isWall()
{
	return (this->weight == 1);
}

void Node::setAsVisited()
{
	loadTexture("visited.png");
}

void Node::setAsPath()
{
	loadTexture("path.png");
}

Node::~Node()
{
}
