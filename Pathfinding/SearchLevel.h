#pragma once
#include <vector>
#include <cmath> // For .cpp calculations
#include "SearchNode.h"

class SearchLevel
{
public:
	SearchLevel(const uint8_t* inputData, int width, int height);
	~SearchLevel();

	float calculateG(SearchNode* fromNode, SearchNode* toNode);
	float calculateH(Position fromPos, Position toPos);

	// Not walkable if the coordinate pixel is green.
	bool isWalkable(int x, int y);
	
	std::vector<Position> getAdjacentNodes(int posX, int posY);

private:
	const uint8_t* inputData = 0;
	int width = 0;
	int height = 0;
};
