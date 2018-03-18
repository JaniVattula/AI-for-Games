#pragma once
#include <vector>
#include <cmath> // For .cpp calculations
#include "SearchNode.h"

class SearchLevel
{
public:
	SearchLevel();
	~SearchLevel();

	float calculateG(SearchNode* fromNode, SearchNode* toNode);
	float calculateH(SearchNode* fromNode, SearchNode* toNode);

	bool isWalkable(int x, int y);
	
	std::vector<Position> getAdjacentNodes(int posX, int posY);
};
