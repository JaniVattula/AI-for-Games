#pragma once
#include <utility>

typedef std::pair<int, int> Position;

class SearchNode
{
public:
	SearchNode(const Position &currentPosition, float _H, float deltaG, SearchNode* prev);
	~SearchNode();

	float getDistance() const;	// Returns approximation of the total path cost
	void resetPrev(SearchNode* prev, float deltaG);

	// Less-than function for sorting
	static bool isLessThan(SearchNode* n1, SearchNode* n2)
	{
		return n1->getDistance() > n2->getDistance();
	}

// Public search node variables
	SearchNode* prevNode;	// Previous/parent node from which arrived to this
	Position pos;			// X and Y position in the map
	float G;				// Actual distance from beginning point (pathfinding A)
	float H;				// Estimated distance to end point (pathfinding B)
	float F;				// G + H
};