#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Node.h"

class Map
{
public:
	Map(std::string fileName);
	std::vector<Node*>& getNodesMap();
	unsigned int getWidth();
	unsigned int getHeight();
	Node* findNodeOnMap(Vector2int coords);
	void render(sf::RenderWindow* window);
	~Map();

private:
	std::vector<Node*> nodesMap;
	unsigned int width, height;
};

