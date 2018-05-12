#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Vector2int {
	int x, y;

	bool operator== (Vector2int& coords);
	Vector2int operator+ (Vector2int& coords);
};


class Node : public sf::Sprite
{
public:
	int weight;
	float g, h;
	Vector2int coords;
	Node* parent;
	sf::Texture* texture;

public:
	Node();
	Node(Vector2int coords, int weight);
	unsigned int getTotalScore();
	void loadTexture(std::string fileName);
	void setAsVisited();
	void setAsPath();
	bool isWall();
	~Node();
};

