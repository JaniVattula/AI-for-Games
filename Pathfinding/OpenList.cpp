#include <algorithm>
#include "OpenList.h"

OpenList::OpenList()
{
}

OpenList::~OpenList() {}

// Sort the open list using a comparison functor, defined in OpenList.h
void OpenList::sortOpenList()
{
	std::sort(openList.begin(), openList.end(), comp());
}

// Push back the node pointer to open list
void OpenList::insertToOpenList(SearchNode* node)
{
	openList.push_back(node);
}

// Loop through the open list to find node at position
SearchNode* OpenList::findFromOpenList(Position pos_)
{
	for (int i = 0; i < openList.size(); i++)
	{
		if (openList[i]->pos == pos_)
		{
			return openList[i];
		}
	}
}

SearchNode* OpenList::removeSmallestF()
{
	return nullptr;
}

// Simple empty check using standard vector functionality
bool OpenList::isEmpty()
{
	return openList.empty();
}

// Simple clearing function using standard vector functionality
void OpenList::clear()
{
	openList.clear();
}

