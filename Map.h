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
	Node* getStartNode();
	Node* getEndNode();
	void render(sf::RenderWindow* window);
	void setStart(float x, float y);
	void setEnd(float x, float y);
	~Map();

private:
	std::vector<Node*> nodesMap;
	unsigned int width, height;
	Node* startNode;
	Node* endNode;
};

