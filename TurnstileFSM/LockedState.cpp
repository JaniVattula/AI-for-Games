#include "LockedState.h"

LockedState::LockedState()
{

}

LockedState::~LockedState()
{

}

Action LockedState::coin()
{
	std::cout << "Locked - Coin\n";
	return Unlock;
}

Action LockedState::pass()
{
	std::cout << "Locked - Pass\n";
	return Alarm;
}

Action LockedState::ready()
{
	std::cout << "Locked - Ready\n";
	return Default;
}

Action LockedState::reset()
{
	std::cout << "Locked - Reset\n";
	return Default;
}