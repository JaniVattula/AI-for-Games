#pragma once
#include <vector>
#include "SearchNode.h"

// A comparison functor for SearchNode elements
struct comp
{
	bool operator()(const SearchNode* first, const SearchNode* second)
	{
		return first->F < second->F;
	}
};

class OpenList
{
public:
	OpenList();
	~OpenList();

	void sortOpenList();
	void insertToOpenList(SearchNode* node);
	SearchNode* findFromOpenList(Position pos_);
	SearchNode* removeSmallestF();	// TODO Ensure the function is efficient

	bool isEmpty();
	void clear();

private:
	std::vector<SearchNode*> openList;
};