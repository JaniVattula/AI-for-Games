#include "UnlockedState.h"

UnlockedState::UnlockedState()
{

}

UnlockedState::~UnlockedState()
{

}

Action UnlockedState::coin()
{
	std::cout << "Unlocked - Coin\n";
	return Thank;
}

Action UnlockedState::pass()
{
	std::cout << "Unlocked - Pass\n";
	return Lock;
}

Action UnlockedState::ready()
{
	std::cout << "Unlocked - Ready\n";
	return Default;
}

Action UnlockedState::reset()
{
	std::cout << "Unlocked - Reset\n";
	return Default;
}