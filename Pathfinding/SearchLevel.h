#pragma once
#include <vector>
#include "SearchNode.h"

struct vec2
{
	int x = 0;
	int y = 0;
};

class SearchLevel
{
public:
	SearchLevel();
	~SearchLevel();

	float calculateG(SearchNode* fromNode, SearchNode* toNode);
	float calculateH(SearchNode* fromNode, SearchNode* toNode);

	bool isWalkable(int x, int y);
	
	std::vector<vec2> getAdjacentNodes(int posX, int posY);
};

