#pragma once
#include <vector>
#include "SearchNode.h"

class ClosedList
{
public:
	ClosedList();
	~ClosedList();

	void addToClosedList(SearchNode* node);
	bool isInClosedList(Position pos);
	void clear();

private:
	std::vector<SearchNode*> closedList;
};