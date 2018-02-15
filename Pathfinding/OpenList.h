#pragma once
#include "SearchNode.h"

class OpenList
{
public:
	OpenList();
	~OpenList();

	void sortOpenList();
	void insertToOpenList(SearchNode* node);
	SearchNode* findFromOpenList(Position pos);
	SearchNode* removeSmallestF();

	bool isEmpty();
	void clear();

};

