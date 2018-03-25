#include "SearchNode.h"


SearchNode::SearchNode(const Position &currentPosition, float _H, float deltaG, SearchNode* prev)
{
	prevNode = 0;
	pos = currentPosition;
	G = 0;
	H = _H;

	resetPrev(prev, deltaG);
}

SearchNode::~SearchNode() {}
SearchNode::SearchNode() {}

float SearchNode::getDistance() const { return F; }

// Calculates total G for this node from the previous node's G value, and updates F
void SearchNode::resetPrev(SearchNode* prev, float deltaG)
{
	prevNode = prev;

	if (prev == 0)
	{
		G = 0.0f;
	}
	else
	{
		G = deltaG + prev->G;
	}

	F = H + G;
}