#include "ClosedList.h"


ClosedList::ClosedList()
{
}

ClosedList::~ClosedList() {}

// Push back the node pointer to closed list
void ClosedList::addToClosedList(SearchNode* node)
{
	closedList.push_back(node);
}

// Iterate through the closed list, checking for a matching position
bool ClosedList::isInClosedList(Position pos_)
{
	for (unsigned int i = 0; i < closedList.size(); i++)
	{
		if (closedList[i]->pos == pos_)
		{
			return true;
		}
	}

	return false;
}

// Simple clearing function using standard vector functionality
void ClosedList::clear()
{
	closedList.clear();
}
