#pragma once
#include "SearchNode.h"

class ClosedList
{
public:
	ClosedList();
	~ClosedList();

	void addToClosedList(SearchNode* node);
	bool isInClosedList(Position pos);
	void clear();

};