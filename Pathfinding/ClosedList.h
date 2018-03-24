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

	int getSize() {	return closedList.size(); }
	void setCheckLimit(int limit) {	checkLimit = limit;	}
	int getCheckLimit() { return checkLimit; }


private:
	std::vector<SearchNode*> closedList;
	int checkLimit = 1000;
};