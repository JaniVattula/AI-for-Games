#include "LockedState.h"

LockedState::LockedState()
{

}

LockedState::~LockedState()
{

}

Action LockedState::coin()
{
	std::cout << "Previous state: Locked \nEvent: Coin \nUnlocking gate.\n";
	return Unlock;
}

Action LockedState::pass()
{
	std::cout << "Previous state: Locked \nEvent: Pass \nUnauthorized pass! Alarm!\n";
	return Alarm;
}

Action LockedState::ready()
{
	std::cout << "Previous state: Locked \nEvent: Ready\n";
	return Default;
}

Action LockedState::reset()
{
	std::cout << "Previous state: Locked \nEvent: Reset\n";
	return Default;
}