#include "LockedState.h"

LockedState::LockedState()
{

}

LockedState::~LockedState()
{

}

void LockedState::coin(TurnstileFSM* machine)
{
	std::cout << "Locked - Coin\n";
	machine->getTurnstile()->unlock();
}

void LockedState::pass(TurnstileFSM* machine)
{
	std::cout << "Locked - Pass\n";
}

void LockedState::ready(TurnstileFSM* machine)
{
	std::cout << "Locked - Ready\n";
}

void LockedState::reset(TurnstileFSM* machine)
{
	std::cout << "Locked - Reset\n";
}