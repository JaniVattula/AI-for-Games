#include "SearchLevel.h"


SearchLevel::SearchLevel(const uint8_t* inputData, int width, int height)
{
	this->inputData = inputData;
	this->width = width;
	this->height = height;
}

SearchLevel::SearchLevel() {}
SearchLevel::~SearchLevel() {}

// Calculate the actual distance from the pathfinding start point
float SearchLevel::calculateG(SearchNode* fromNode, SearchNode* toNode)
{
	// Distance on X and Y axis is 1
	// Distance on XY dir is 1.41 (square root of 2)

	// Add the distance already traveled to the new travel step (new H)
	// H will return 1 or 1.41 depending on the direction traveled, but
	// also works for longer distances (teleportation possibilities?)
	return (fromNode->G + calculateH(fromNode, toNode));
}

// Calculate the optimal distance to the pathfinding end point
float SearchLevel::calculateH(SearchNode* fromNode, SearchNode* toNode)
{
	// Distance on X and Y axis is 1
	// Distance on XY dir is 1.41 (square root of 2)
	// Calculate optimal theoretical route from fromPos to toPos

	// Calculate the absolute distances for each axis
	unsigned int distanceX = abs(fromNode->pos.first - toNode->pos.first);
	unsigned int distanceY = abs(fromNode->pos.second - toNode->pos.second);
	
	// Assume as many XY moves as possible
	// Add the remaining distance, which is a straight line
	if (distanceX < distanceY)
	{
		return (distanceX * 1.41f + (distanceY - distanceX));
	}
	else if (distanceX > distanceY)
	{
		return (distanceY * 1.41f + (distanceX - distanceY));
	}

	// If we end up here the distances are equal, and we can use all XY moves
	return (distanceX * 1.41f);
}

// Checks the coordinate colors from inputData, (0, 255, 0) is not walkable.
bool SearchLevel::isWalkable(int x, int y)
{
	const uint8_t* pixel = &inputData[3 * (y * width + x)];

	uint8_t red = pixel[0];
	uint8_t green = pixel[1];
	uint8_t blue = pixel[2];

	// If it's a green pixel, we can't walk on it
	if (red == 0 && green == 255 && blue == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::vector<Position> SearchLevel::getAdjacentNodes(int posX, int posY)
{
	int vecIndex = 0;
	std::vector<Position> adjacentNodes;
	adjacentNodes.reserve(8);

	// Loop will find the adjacent 8 Positions, and ignore the target (0,0) position.
	// Get positions from -1, 0, and 1 x-distance from target
	for (int x = -1; x <= 1; x++)
	{
		// Get positions from -1, 0 and 1 y-distance from target
		for (int y = -1; y <= 1; y++)
		{
			if (x != 0 && y != 0)	// Ignore target position
			{
				// TODO Check if the node is walkable
				adjacentNodes[vecIndex].first = (posX + x);
				adjacentNodes[vecIndex].second = (posY + y);
				vecIndex++;
			}
		}
	}

	return adjacentNodes;
}
