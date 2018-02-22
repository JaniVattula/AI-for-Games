#include "SearchLevel.h"


SearchLevel::SearchLevel()
{
}

SearchLevel::~SearchLevel() {}

float SearchLevel::calculateG(SearchNode* fromNode, SearchNode* toNode)
{
	return 0.0f;
}

float SearchLevel::calculateH(SearchNode* fromNode, SearchNode* toNode)
{
	return 0.0f;
}

bool SearchLevel::isWalkable(int x, int y)
{
	return false;
}

std::vector<Position> SearchLevel::getAdjacentNodes(int posX, int posY)
{
	int vecIndex = 0;
	std::vector<Position> adjacentNodes;
	adjacentNodes.reserve(8);

	// Loop will find the adjacent 8 Positions, and ignore the target (0,0) position.
	// Get positions from -1, 0, and 1 x-distance from target
	for (int x = -1; x <= 1; x++)
	{
		// Get positions from -1, 0 and 1 y-distance from target
		for (int y = -1; y <= 1; y++)
		{
			if (x != 0 && y != 0)	// Ignore target position
			{
				adjacentNodes[vecIndex].first = (posX + x);
				adjacentNodes[vecIndex].second = (posY + y);
				vecIndex++;
			}
		}
	}

	return adjacentNodes;
}
