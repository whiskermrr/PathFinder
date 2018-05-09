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
	g = h = 0;
}

unsigned int Node::getTotalScore()
{
	return g + h;
}


Node::~Node()
{
}
