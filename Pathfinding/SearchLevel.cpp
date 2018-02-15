#include "SearchLevel.h"


SearchLevel::SearchLevel()
{
}

SearchLevel::~SearchLevel() {}

float SearchLevel::calculateG(SearchNode * fromNode, SearchNode * toNode)
{
	return 0.0f;
}

float SearchLevel::calculateH(SearchNode * fromNode, SearchNode * toNode)
{
	return 0.0f;
}

bool SearchLevel::isWalkable(int x, int y)
{
	return false;
}

std::vector<Position> SearchLevel::getAdjacentNodes(int posX, int posY)
{
	return std::vector<Position>();
}
