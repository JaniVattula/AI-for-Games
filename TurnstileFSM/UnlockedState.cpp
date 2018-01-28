#include "UnlockedState.h"

UnlockedState::UnlockedState()
{

}

UnlockedState::~UnlockedState()
{

}

Action UnlockedState::coin()
{
	std::cout << "Previous state: Unlocked \nEvent: Coin \n";
	return Thank;
}

Action UnlockedState::pass()
{
	std::cout << "Previous state: Unlocked \nEvent: Pass\nGate passed, locking gate.\n";
	return Lock;
}

Action UnlockedState::ready()
{
	std::cout << "Previous state: Unlocked \nEvent: Ready\n";
	return Default;
}

Action UnlockedState::reset()
{
	std::cout << "Previous state: Unlocked \nEvent: Reset\n";
	return Default;
}