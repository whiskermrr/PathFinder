#pragma once


struct Vector2int {
	int x, y;

	bool operator== (Vector2int& coords);
	Vector2int operator+ (Vector2int& coords);
};


class Node
{
public:
	int weight;
	unsigned int g, h;
	Vector2int coords;
	Node* parent;

public:
	Node();
	Node(Vector2int coords, int weight);
	unsigned int getTotalScore();
	~Node();
};

